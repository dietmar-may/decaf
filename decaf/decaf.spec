Name:           decaf
Version:        3.9.4
Release:        1%{?dist}
Summary:        C++ Implementation of core Java classes

Group:          Development/Libraries
License:        ASL 2.0
URL:            https://github.com/dietmar-may/decaf
Source0:        http://www.apache.org/dist/activemq/activemq-cpp/source/activemq-cpp-library-%{version}-src.tar.gz
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

BuildRequires:  doxygen
BuildRequires:  graphviz
%if %{?fedora}%{!?fedora:0} >= 9 || %{?rhel}%{!?rhel:0} >= 6
BuildRequires:  tex(latex)
%else
BuildRequires:  tetex-latex
%endif

BuildRequires:  automake >= 1.10
BuildRequires:  autoconf >= 2.63
BuildRequires:  libtool  >= 1.5.24
BuildRequires:  apr-devel%{?_isa} >= 1.3
BuildRequires:  cppunit-devel%{?_isa} >= 1.10.2
BuildRequires:  openssl-devel%{?_isa} >= 0.98.0

%description
decaf is a core Java-like API for C++.

%package        devel
Summary:        Development files for using the %{name} library
Group:          Development/Libraries
Requires:       %{name} = %{version}-%{release}
Requires:       pkgconfig

%description    devel
decaf is a core Java-like API for C++.

The %{name}-devel package contains header files for developing
applications that use %{name} to communicate with the Decaf
core Java API for C++.

%{name}-devel contains development header files.

%package doc
Summary:        C++ implementation header files for core Java
Group:          Documentation for the CMS API
%if %{?fedora}%{!?fedora:0} >= 10 || %{?rhel}%{!?rhel:0} >= 6
BuildArch:      noarch
%endif

%description doc
decaf is a core Java-like API for C++.

%{name}-doc contains api documentation.

%prep
%setup -q -n decaf-library-%{version}

%build
./autogen.sh
# Build pdf(30MB) rather than default html(400MB).
%configure --disable-static --disable-doxygen-html --enable-doxygen-pdf
make %{?_smp_mflags}
make %{?_smp_mflags}  doxygen-run
make %{?_smp_mflags} doxygen-pdf

%install
rm -rf $RPM_BUILD_ROOT
make install DESTDIR=$RPM_BUILD_ROOT
find $RPM_BUILD_ROOT -name '*.la' -exec rm -f {} ';'
rm $RPM_BUILD_ROOT/%{_bindir}/example

%clean
rm -rf $RPM_BUILD_ROOT

%check
make %{?_smp_mflags} check

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-,root,root,-)
%{_libdir}/lib%{name}-%{version}.so.*
%doc LICENSE.txt  NOTICE.txt  README.txt  RELEASE_NOTES.txt

%files devel
%defattr(-,root,root,-)
%{_libdir}/lib%{name}-%{version}.so
%{_includedir}/%{name}
%{_libdir}/pkgconfig/%{name}.pc
%{_bindir}/decaf-config

%files doc
%defattr(-,root,root,-)
%doc doc/%{name}.pdf

%changelog

* Tue Nov 7 2017 Dietmar May <dietmar.may@outlook.com> - 3.9.5
- Stripped down ActiveMQ-CPP 3.9.5 to decaf-only version.
* Wed Sep 08 2010 Tim Bish <tabish121@gmail.com> - 3.2.3
- Create a new Spec by porting the Fedora Version.
