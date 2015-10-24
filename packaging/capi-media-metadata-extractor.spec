Name:       capi-media-metadata-extractor
Summary:    A media metadata extractor library in SLP C API
Version: 0.1.14
Release:    1
Group:      System/Libraries
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
BuildRequires:  cmake
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(mm-fileinfo)
BuildRequires:  pkgconfig(capi-base-common)
Requires(post): /sbin/ldconfig
Requires(postun): /sbin/ldconfig

%description
A media metadata extractor  library in SLP C API

%package devel
Summary:  A media metadata extractor  library in SLP C API (Development)
Group:    Multimedia/Development
Requires: %{name} = %{version}-%{release}

%description devel
A media metadata extractor  library in SLP C API

%prep
%setup -q


%build
export CFLAGS+=" -Wextra -Wno-array-bounds"
export CFLAGS+=" -Wno-ignored-qualifiers -Wno-unused-parameter -Wshadow"
export CFLAGS+=" -Wwrite-strings -Wswitch-default"

MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`

cmake . -DCMAKE_INSTALL_PREFIX=/usr -DFULLVER=%{version} -DMAJORVER=${MAJORVER}


make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install
mkdir -p %{buildroot}/%{_datadir}/license
cp -rf %{_builddir}/%{name}-%{version}/LICENSE.APLv2.0 %{buildroot}/%{_datadir}/license/%{name}
%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig


%files
%manifest %{name}.manifest
%{_libdir}/libcapi-media-metadata-extractor.so
%{_datadir}/license/%{name}

%files devel
%{_includedir}/media/*.h
%{_libdir}/pkgconfig/capi-media-metadata-extractor.pc
