Name:		openadsi
Version:	0.0.4
Release:	1%{?dist}
Summary:	Open Adaptive Security Initiative
Group:		System Environment/Daemons	
License: 	GPLv2+	
URL:		http://code.google.com/p/openadsi/
Source0:	http://openadsi.googlecode.com/files/openadsi-0.0.4.tar.gz
BuildRoot:	%{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
BuildRequires:	audit-libs-python
BuildRequires:	audit-libs-devel
BuildRequires:	python
BuildRequires:	audit 
Requires: chkconfig

%description
OpenAdSI (Open Adaptive Security Initiative) is tool for monitoring
and responding to Audit events in real-time, allowing for custom
plug-in modules.

%post
/sbin/chkconfig --add openadsi
/sbin/chkconfig --add openadsimgr
/sbin/chkconfig --add openadsidb
/sbin/chkconfig --add openadsiplugin


%prep
%setup -q


%build
%configure --sbindir=/sbin
make %{?_smp_mflags}


%install
rm -rf $RPM_BUILD_ROOT
mkdir -p $RPM_BUILD_ROOT/%{_var}/log/openadsi/lock
mkdir -p $RPM_BUILD_ROOT/%{_sysconfdir}/openadsi
mkdir -p $RPM_BUILD_ROOT/%{_sysconfdir}/openadsi/plugins.d
mkdir -p $RPM_BUILD_ROOT/%{_initrddir}
mkdir -p $RPM_BUILD_ROOT/%{_sysconfdir}/audisp/plugins.d
make install DESTDIR=$RPM_BUILD_ROOT


%check
make check

%clean
# comment this out until it is fixed
rm -rf $RPM_BUILD_ROOT


%files
%defattr(-,root,root,-)
%doc AUTHORS COPYING ChangeLog README TODO
%attr(750,root,root) /sbin/audisp-openadsi
%attr(750,root,root) /sbin/openadsihb
%attr(750,root,root) /sbin/openadsimgr
%attr(750,root,root) /sbin/openadsidb
%attr(750,root,root) /sbin/openadsiplugin
%attr(750,root,root) /usr/bin/opeek
%attr(750,root,root) /usr/bin/opeekmgr
%attr(750,root,root) /usr/bin/opeekplugin
%attr(640,root,root) /etc/audisp/plugins.d/audisp-openadsi.conf
%config(noreplace) %attr(640,root,root) /etc/openadsi/Makefile
%config(noreplace) %attr(640,root,root) /etc/openadsi/client.cnf
%config(noreplace) %attr(640,root,root) /etc/openadsi/root.cnf
%config(noreplace) %attr(640,root,root) /etc/openadsi/serverCA.cnf
%config(noreplace) %attr(640,root,root) /etc/openadsi/server.cnf
#%attr(640,root,root) /etc/openadsi/openadsi.conf
%attr(750,root,root) /etc/rc.d/init.d/openadsi
%attr(750,root,root) /etc/rc.d/init.d/openadsimgr
%attr(750,root,root) /etc/rc.d/init.d/openadsidb
%attr(750,root,root) /etc/rc.d/init.d/openadsiplugin
%attr(644,root,root) /etc/openadsi/openadsi.te
%attr(750,root,root) /etc/openadsi/fixselinux.sh
%attr(640,root,root) /var/log/openadsi/lock/openadsihb
%attr(640,root,root) /var/log/openadsi/lock/openadsimgr
%attr(640,root,root) /var/log/openadsi/lock/openadsidb
%attr(640,root,root) /var/log/openadsi/lock/openadsiplugin


%attr(644,root,root) %{_mandir}/man1/openadsi.1.gz
#%{_prefix}/include/*
%config(noreplace) %attr(640,root,root) /etc/openadsi/openadsi.conf



%changelog
* Sat Feb  7 2009 Mike Chirico <mchirico@gmail.com> 0.0.7-1
- First rpm release.
