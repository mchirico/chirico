import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.net.Socket;
import java.security.KeyManagementException;
import java.security.KeyStore;
import java.security.KeyStoreException;
import java.security.NoSuchAlgorithmException;
import java.security.Principal;
import java.security.PrivateKey;
import java.security.UnrecoverableKeyException;
import java.security.cert.Certificate;
import java.security.cert.CertificateException;
import java.security.cert.X509Certificate;

import javax.net.ssl.HttpsURLConnection;
import javax.net.ssl.KeyManager;
import javax.net.ssl.SSLContext;
import javax.net.ssl.SSLSocketFactory;
import javax.net.ssl.TrustManager;
import javax.net.ssl.TrustManagerFactory;
import javax.net.ssl.X509KeyManager;


/**
 * @author Gideon
 * 
 */
public class SSLv3Context {

    private String keyStorePassword;

    private String keyStoreFileName;

    private String certificateAlias;

    private String certificatePassword;

    public SSLv3Context(String keyStorePassword, String keyStoreFileName, String certificateAlias, String certificatePassword) {

this.setKeyStorePassword(keyStorePassword);
this.setKeyStoreFileName(keyStoreFileName);
this.setCertificateAlias(certificateAlias);
this.setCertificatePassword(certificatePassword);

SSLContext sc;
try {
    sc = SSLContext.getInstance("SSLv3");

    final KeyStore keystore = KeyStore.getInstance("jks");
    FileInputStream fis = new FileInputStream(this.getKeyStoreFileName());
    keystore.load(fis, this.getKeyStorePassword());
    fis.close();

    TrustManagerFactory factory = TrustManagerFactory.getInstance(TrustManagerFactory.getDefaultAlgorithm());
    factory.init(keystore);

    TrustManager[] trustmanagers = factory.getTrustManagers();
    if (trustmanagers.length == 0) {
throw new NoSuchAlgorithmException("no trust manager found");
    }

    KeyManager[] km = new KeyManager[] { new X509KeyManager() {

public String chooseClientAlias(String[] arg0, Principal[] arg1, Socket arg2) {
    return getCertificateAlias();
}

public String chooseServerAlias(String arg0, Principal[] arg1, Socket arg2) {
    return null;
}

public X509Certificate[] getCertificateChain(String arg0) {
    try {
Certificate[] cert = keystore.getCertificateChain(getCertificateAlias());
return new X509Certificate[] { (X509Certificate) cert[0] };
    } catch (KeyStoreException e) {
e.printStackTrace();
    }
    return null;
}

public String[] getClientAliases(String arg0, Principal[] arg1) {
    return null;
}

public PrivateKey getPrivateKey(String arg0) {
    try {
return (PrivateKey) keystore.getKey(getCertificateAlias(), getCertificatePassword());
    } catch (KeyStoreException e) {
e.printStackTrace();
    } catch (NoSuchAlgorithmException e) {
e.printStackTrace();
    } catch (UnrecoverableKeyException e) {
e.printStackTrace();
    }
    return null;
}

public String[] getServerAliases(String arg0, Principal[] arg1) {
    return null;
}

    } };

    sc.init(km, trustmanagers, new java.security.SecureRandom());
    SSLSocketFactory sslSocketFactory = sc.getSocketFactory();
    HttpsURLConnection.setDefaultSSLSocketFactory(sslSocketFactory);
    
} catch (NoSuchAlgorithmException e1) {
    e1.printStackTrace();
} catch (KeyStoreException e) {
    e.printStackTrace();
} catch (FileNotFoundException e) {
    e.printStackTrace();
} catch (CertificateException e) {
    e.printStackTrace();
} catch (IOException e) {
    e.printStackTrace();
} catch (KeyManagementException e) {
    e.printStackTrace();
}
    }

    /**
         * @return the certificateAlias
         */
    public String getCertificateAlias() {
return this.certificateAlias;
    }

    /**
         * @param certificateAlias
         *                the certificateAlias to set
         */
    public void setCertificateAlias(String certificateAlias) {
this.certificateAlias = certificateAlias;
    }

    /**
         * @return the certificatePassword
         */
    public char[] getCertificatePassword() {
return this.certificatePassword.toCharArray();
    }

    /**
         * @param certificatePassword
         *                the certificatePassword to set
         */
    public void setCertificatePassword(String certificatePassword) {
this.certificatePassword = certificatePassword;
    }

    /**
         * @return the keyStoreFileName
         */
    public String getKeyStoreFileName() {
return this.keyStoreFileName;
    }

    /**
         * @param keyStoreFileName
         *                the keyStoreFileName to set
         */
    public void setKeyStoreFileName(String keyStoreFileName) {
this.keyStoreFileName = keyStoreFileName;
    }

    /**
         * @return the keyStorePassword
         */
    private char[] getKeyStorePassword() {
return this.keyStorePassword.toCharArray();
    }

    /**
         * @param keyStorePassword
         *                the keyStorePassword to set
         */
    public void setKeyStorePassword(String keyStorePassword) {
this.keyStorePassword = keyStorePassword;
    }
}