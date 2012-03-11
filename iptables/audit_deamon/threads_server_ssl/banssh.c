#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <libaudit.h>
#include <auparse.h>
#include <syslog.h>
#include "common.h"






#define CIPHER_LIST "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH"
#define CAFILE "/etc/banssh/rootcert.pem"
#define CADIR "/etc/banssh"
#define CERTFILE "/etc/banssh/client.pem"

#define MAXLOGINS 3


FILE *Popen(const char *command, const char *mode)
{
	FILE *fp;

	if ((fp = popen(command, mode)) == NULL)
		syslog(LOG_ERR, "popen error");
	return (fp);
}

int Pclose(FILE * fp)
{
	int n;

	if ((n = pclose(fp)) == -1)
		syslog(LOG_ERR, "pclose error");
	return (n);
}

char *Fgets(char *ptr, int n, FILE * stream)
{
	char *rptr;

	if ((rptr = fgets(ptr, n, stream)) == NULL && ferror(stream))
		syslog(LOG_ERR, "fgets error");

	return (rptr);
}

void Fputs(const char *ptr, FILE * stream)
{
	if (fputs(ptr, stream) == EOF)
		syslog(LOG_ERR, "fputs error");
}



extern int errno;

#define MAXLINE 1024





SSL_CTX *setup_client_ctx(void)
{
	SSL_CTX *ctx;

	ctx = SSL_CTX_new(SSLv23_method());
	if (SSL_CTX_load_verify_locations(ctx, CAFILE, CADIR) != 1)
		int_error("Error loading CA file and/or directory");
	if (SSL_CTX_set_default_verify_paths(ctx) != 1)
		int_error
		    ("Error loading default CA file and/or directory");
	if (SSL_CTX_use_certificate_chain_file(ctx, CERTFILE) != 1)
		int_error("Error loading certificate from file");
	if (SSL_CTX_use_PrivateKey_file(ctx, CERTFILE, SSL_FILETYPE_PEM) !=
	    1)
		int_error("Error loading private key from file");
	SSL_CTX_set_verify(ctx, SSL_VERIFY_PEER, verify_callback);
	SSL_CTX_set_verify_depth(ctx, 4);
	SSL_CTX_set_options(ctx, SSL_OP_ALL | SSL_OP_NO_SSLv2);
	if (SSL_CTX_set_cipher_list(ctx, CIPHER_LIST) != 1)
		int_error("Error setting cipher list (no valid ciphers)");
	return ctx;
}


/*
static void auparse_callback_orig(auparse_state_t * au,
				  auparse_cb_event_t cb_event_type,
				  void *user_data)
{
	int *event_cnt = (int *) user_data;
	int record_cnt;
	FILE *fp;
	char buf[MAXLINE];

	if (cb_event_type == AUPARSE_CB_EVENT_READY) {
		if (auparse_first_record(au) <= 0) {
			syslog(LOG_ERR,"can't get first record\n");
			return;
		}
		syslog(LOG_ERR,"event %d has %d records\n", *event_cnt,
		       auparse_get_num_records(au));
		record_cnt = 1;
		do {
			if (auparse_get_type(au) == 1112) {

				fp = Popen("/sbin/AttacksAudit.py", "r");

				while (Fgets(buf, MAXLINE, fp) != NULL)
					Fputs(buf, stdout);

				Pclose(fp);

			}

			printf
			    ("    record %d of type %d(%s) has %d fields\n",
			     record_cnt, auparse_get_type(au),
			     audit_msg_type_to_name(auparse_get_type(au)),
			     auparse_get_num_fields(au));
			syslog(LOG_ERR,"    line=%d file=%s\n",
			       auparse_get_line_number(au),
			       auparse_get_filename(au) ?
			       auparse_get_filename(au) : "None");
			const au_event_t *e = auparse_get_timestamp(au);
			if (e == NULL) {
				return;
			}
			syslog(LOG_ERR,"    event time: %u.%u:%lu, host=%s\n",
			       (unsigned) e->sec,
			       e->milli, e->serial,
			       e->host ? e->host : "?");
			auparse_first_field(au);
			do {
				syslog(LOG_ERR,"        %s=%s (%s)\n",
				       auparse_get_field_name(au),
				       auparse_get_field_str(au),
				       auparse_interpret_field(au));
			} while (auparse_next_field(au) > 0);
			syslog(LOG_ERR,"\n");
			record_cnt++;
		} while (auparse_next_record(au) > 0);
		(*event_cnt)++;
	}
}
*/

static void auparse_callback(auparse_state_t * au,
			     auparse_cb_event_t cb_event_type,
			     void *user_data)
{
	int *event_cnt = (int *) user_data;
	int record_cnt;
	static int login_cnt = 0;
	FILE *fp;
	char buf[MAXLINE];
	char acct[MAXLINE];
	char addr[MAXLINE];





	if (cb_event_type == AUPARSE_CB_EVENT_READY) {
		if (auparse_first_record(au) <= 0) {
			syslog(LOG_ERR, "can't get first record\n");
			return;
		}
		/*
		   syslog(LOG_ERR,"login_cnt(%d) event %d has %d records\n",login_cnt, *event_cnt,
		   auparse_get_num_records(au)); */
		record_cnt = 1;
		do {
			if (auparse_get_type(au) == 1112) {
				acct[0] = '\0';
				addr[0] = '\0';

				printf
				    ("login_cnt(%d) record %d of type %d(%s) has %d fields\n",
				     login_cnt,
				     record_cnt, auparse_get_type(au),
				     audit_msg_type_to_name
				     (auparse_get_type(au)),
				     auparse_get_num_fields(au));
				syslog(LOG_ERR, "    line=%d file=%s\n",
				       auparse_get_line_number(au),
				       auparse_get_filename(au) ?
				       auparse_get_filename(au) : "None");
				const au_event_t *e =
				    auparse_get_timestamp(au);
				if (e == NULL) {
					return;
				}
				printf
				    ("    event time: %u.%u:%lu, host=%s\n",
				     (unsigned) e->sec, e->milli,
				     e->serial, e->host ? e->host : "?");
				auparse_first_field(au);
				do {

					syslog(LOG_ERR,
					       "        %s=%s (%s)\n",
					       auparse_get_field_name(au),
					       auparse_get_field_str(au),
					       auparse_interpret_field
					       (au));


					if (strncmp
					    (auparse_get_field_name(au),
					     "addr", 4) == 0) {
						snprintf(addr, MAXLINE,
							 "%s",
							 auparse_interpret_field
							 (au));
						syslog(LOG_ERR, "YES1\n");
					}
					if (strncmp
					    (auparse_get_field_name(au),
					     "acct", 4) == 0) {
						snprintf(acct, MAXLINE,
							 "%s",
							 auparse_interpret_field
							 (au));
						syslog(LOG_ERR, "YES2\n");
					}

					if (strncmp
					    (auparse_get_field_name(au),
					     "res", 3) == 0) {
						if (strncmp
						    (auparse_interpret_field
						     (au), "failed",
						     6) == 0) {
							login_cnt++;

						}
					}

				} while (auparse_next_field(au) > 0);

				// Total logins for everything
				if (login_cnt >= MAXLOGINS) {
					fp = Popen("/sbin/AttacksAudit.py",
						   "r");
					while (Fgets(buf, MAXLINE, fp) !=
					       NULL)
						syslog(LOG_ERR, "%s", buf);
					Pclose(fp);

					printf
					    ("\n login_cnt(%d),acct=(%s),addr=(%s)\n",
					     login_cnt, acct, addr);
					login_cnt = 0;
				}

				record_cnt++;


			}


		} while (auparse_next_record(au) > 0);
		(*event_cnt)++;
	}
}

int do_client_loop(SSL * ssl)
{
	int err, nread, len;
	char buf[1024];
	buf[0] = '\0';

	auparse_state_t *au;
	int event_cnt = 1;
	au = auparse_init(AUSOURCE_FEED, 0);
	auparse_add_callback(au, auparse_callback, &event_cnt, NULL);

	do {

		/* Maybe this is causing problems? Yeah, I think it is correct now */
		for (nread = 0; nread < sizeof(buf); nread += err) {
			err =
			    SSL_read(ssl, buf + nread,
				     sizeof(buf) - nread);
			buf[nread + err] = '\0';
			//syslog(LOG_ERR, "%s", buf + nread);
			len = err;
			auparse_feed(au, buf + nread, len);
			if (err <= 0)
				break;
		}

	} while (err > 0);

	auparse_flush_feed(au);
	auparse_destroy(au);

	return 1;
}

int main_ssl(int argc, char **argv)
{
	BIO *conn;
	SSL *ssl;
	SSL_CTX *ctx;
	long err;

	init_OpenSSL();
	seed_prng();

	ctx = setup_client_ctx();

	syslog(LOG_ERR, "SERVER= %s:%s\n", SERVER, PORT);
	conn = BIO_new_connect(SERVER ":" PORT);
	if (!conn)
		int_error("Error creating connection BIO");

	if (BIO_do_connect(conn) <= 0)
		int_error("Error connecting to remote machine");

	ssl = SSL_new(ctx);
	SSL_set_bio(ssl, conn, conn);
	if (SSL_connect(ssl) <= 0)
		int_error("Error connecting SSL object");
	if ((err = post_connection_check(ssl, SERVER)) != X509_V_OK) {
		syslog(LOG_ERR, "-Error: peer certificate: %s\n",
		       X509_verify_cert_error_string(err));
		int_error("Error checking SSL object after connection");
	}
	syslog(LOG_ERR, "SSL Connection opened\n");
	if (do_client_loop(ssl))
		SSL_shutdown(ssl);
	else
		SSL_clear(ssl);
	syslog(LOG_ERR, "SSL Connection closed\n");

	SSL_free(ssl);
	SSL_CTX_free(ctx);
	return 0;
}

int main(int argc, char **argv)
{
	int i = 0, j = 0;

	daemon(0, 0);
	syslog(LOG_ERR, "clientparse loaded");
	/* This for loop is is the connection gets dropped.
	   We're the client, and we need to try and connect to the server */
	for (j = 0; j < 1000; ++j) {
		for (i = 0; i < 200; ++i) {
			main_ssl(argc, argv);
			sleep(2 * i);
			syslog(LOG_ERR, "clientparse trying to connect");
		}
	}


	return 0;
}
