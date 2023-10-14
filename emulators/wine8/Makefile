PORTNAME=	wine
DISTVERSION=	8.0.2
CATEGORIES=	emulators
MASTER_SITES=	https://dl.winehq.org/wine/source/8.0/
PKGNAMESUFFIX=	8

MAINTAINER=	teknosquet@danwin1210.de
COMMENT=	Translation layer for Windows programs
WWW=		https://www.winehq.org/

LICENSE=	LGPL21 LGPL3
LICENSE_COMB=	dual
LICENSE_FILE=	${WRKSRC}/LICENSE

ONLY_FOR_ARCHS=	amd64 i386

BUILD_DEPENDS=	${LOCALBASE}/bin/flex:textproc/flex \
		llvm${_LLVM_VERSION}>=0:devel/llvm${_LLVM_VERSION}

USES=		bison cpe desktop-file-utils gmake localbase \
		pkgconfig sdl shebangfix tar:xz
USE_GCC=	yes
USE_SDL=	sdl2

CPE_VENDOR=	winehq

CONFLICTS_INSTALL=	wine wine[0-9] wine-devel wine[0-9]-devel

GNU_CONFIGURE=	yes
CONFIGURE_ARGS+=--disable-kerberos \
		--disable-tests \
		--with-mingw CROSSCC="clang" CROSSCFLAGS="-isystem ${FILESDIR}/clang" \
		--with-opengl \
		--with-pthread \
		--with-sdl \
		--without-alsa \
		--without-capi \
		--without-coreaudio \
		--without-dbus \
		--without-gettext \
		--without-gettextpo \
		--without-gphoto \
		--without-gssapi \
		--without-gstreamer \
		--without-inotify \
		--without-krb5 \
		--without-netapi \
		--without-opencl \
		--without-osmesa \
		--without-pcap \
		--without-sane \
		--without-udev \
		--without-unwind \
		--without-usb
CONFIGURE_ENV=	CPPBIN="${CPP}" FLEX="${LOCALBASE}/bin/flex"
WINELIBDIR=	${PREFIX}/lib
.if !defined(USE_LDCONFIG32)
USE_LDCONFIG=	${WINELIBDIR} ${WINELIBDIR}/wine
.endif
SHEBANG_FILES=	tools/make_requests \
		tools/winemaker/winemaker \
		tools/winedump/function_grep.pl

BINARY_ALIAS+=	clang=${LOCALBASE}/bin/clang${_LLVM_VERSION} \
		lld-link=${LOCALBASE}/bin/lld-link${_LLVM_VERSION}

PORTDATA=	wine.inf

OPTIONS_DEFINE=		DOCS DOSBOX GNUTLS PULSEAUDIO V4L X11
OPTIONS_DEFAULT=	GNUTLS OSS X11
OPTIONS_SUB=		yes

DOCS_DESC=		Bundle documentation
DOSBOX_DESC=		Use DOSBox to run MS-DOS programs
GNUTLS_DESC=		Use TLS protocol
PULSEAUDIO_DESC=	PulseAudio sound support
V4L_DESC=		Video4Linux support

DOSBOX_RUN_DEPENDS=	dosbox:emulators/dosbox

GNUTLS_CONFIGURE_WITH=	gnutls
GNUTLS_LIB_DEPENDS=	libgnutls.so:security/gnutls

OSS_CONFIGURE_ON=		--with-oss

PULSEAUDIO_CONFIGURE_ON=	--with-pulse
PULSEAUDIO_LIB_DEPENDS=		libpulse.so:audio/pulseaudio

V4L_CONFIGURE_WITH=	v4l2
V4L_BUILD_DEPENDS=	${LOCALBASE}/include/linux/videodev2.h:multimedia/v4l_compat
V4L_LIB_DEPENDS=	libv4l2.so:multimedia/libv4l

X11_CONFIGURE_WITH=	x fontconfig freetype opengl xinerama xinput2 xrandr xrender
X11_USES=		gl xorg
X11_USE=		GL=glu XORG=x11,xext,xcomposite,xcursor,xi,xinerama,xrandr,xrender
X11_LIB_DEPENDS=	libfontconfig.so:x11-fonts/fontconfig \
			libfreetype.so:print/freetype2 \
			libvulkan.so:graphics/vulkan-loader

.include <bsd.port.pre.mk>

_LLVM_VERSION = ${LLVM_DEFAULT}

.if ${ARCH} == amd64
CONFIGURE_ARGS+=	--enable-win64 --libdir=${PREFIX}/lib
PLIST_SUB+=		WINE32="@comment " WINE64="" WINEARCH="x86_64"

post-patch:
	${REINPLACE_CMD} "/Exec/s|wine|wine64|g" ${WRKSRC}/loader/wine.desktop

.else
PLIST_SUB+=	WINE32="" WINE64="@comment " WINEARCH="i386"
.endif

post-install:
.if ${ARCH} == i386
	${MV} ${STAGEDIR}${PREFIX}/bin/wineserver ${STAGEDIR}${PREFIX}/bin/wineserver32
	${MV} ${STAGEDIR}${PREFIX}/bin/wine ${STAGEDIR}${PREFIX}/bin/wine.bin
	-${ELFCTL} -e +noaslr ${STAGEDIR}${PREFIX}/bin/wine.bin
	${INSTALL_SCRIPT} ${FILESDIR}/wine.sh ${STAGEDIR}${PREFIX}/bin/wine
.else
	${MV} ${STAGEDIR}${PREFIX}/bin/wine64 ${STAGEDIR}${PREFIX}/bin/wine64.bin
	-${ELFCTL} -e +noaslr ${STAGEDIR}${PREFIX}/bin/wine64.bin
	${INSTALL_SCRIPT} ${FILESDIR}/wine.sh ${STAGEDIR}${PREFIX}/bin/wine64
	${INSTALL_SCRIPT} ${FILESDIR}/wine-wow64.sh ${STAGEDIR}${PREFIX}/bin/wine
	${INSTALL_SCRIPT} ${FILESDIR}/pkg32.sh ${STAGEDIR}${DATADIR}/pkg32.sh
.endif

	@${MKDIR} ${STAGEDIR}${DOCSDIR}
.for i in README ANNOUNCE AUTHORS
	${INSTALL_DATA} ${WRKSRC}/${i} ${STAGEDIR}${DOCSDIR}
.endfor
	${INSTALL_DATA} ${WRKSRC}/programs/winedbg/README ${STAGEDIR}${DOCSDIR}/README.winedbg
	${INSTALL_DATA} ${WRKSRC}/tools/winedump/README ${STAGEDIR}${DOCSDIR}/README.winedump

.include <bsd.port.post.mk>
