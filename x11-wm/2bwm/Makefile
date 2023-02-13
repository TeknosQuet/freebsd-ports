PORTNAME=		2bwm
DISTVERSION=	0.3
CATEGORIES=		x11-wm

MAINTAINER=		TeknosQuet
COMMENT=		Fast floating WM derived from mcwm
WWW=			https://github.com/venam/2bwm

LICENSE=		ISCL

USE_GITHUB=		yes
GH_ACCOUNT=		venam
GH_PROJECT=		2bwm
GH_TAGNAME=		v0.3

LIB_DEPENDS=	libxcb-util.so:x11/xcb-util \
				libxcb-ewmh.so:x11/xcb-util-wm \
				libxcb-icccm.so:x11/xcb-util-wm \
				libxcb-keysyms.so:x11/xcb-util-keysyms \
				libxcb-xrm.so:x11/xcb-util-xrm

USES=			tar:bzip2 xorg
USE_XORG=		xcb xrandr
MAKE_ARGS=		MANPREFIX="${PREFIX}/man"

PLIST_FILES=	bin/2bwm bin/hidden \
				man/man1/2bwm.1.gz man/man1/hidden.1.gz

.include <bsd.port.mk>
