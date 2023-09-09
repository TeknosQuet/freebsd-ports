PORTNAME=		frankenwm
DISTVERSION=	1.0.23
CATEGORIES=		x11-wm

MAINTAINER=		teknosquet@danwin1210.de
COMMENT=		Fast dynamic tiling X11 window manager
WWW=			https://github.com/sulami/FrankenWM

LICENSE=		MIT
LICENSE_FILE=	${WRKSRC}/LICENSE

USE_GITHUB=		yes
GH_ACCOUNT=		sulami
GH_PROJECT=		FrankenWM
GH_TAGNAME=		v1.0.23

BUILD_DEPENDS=	xcb-util-keysyms>0:x11/xcb-util-keysyms \
				xcb-util-wm>0:x11/xcb-util-wm
LIB_DEPENDS=	libxcb-ewmh.so:x11/xcb-util-wm \
				libxcb-icccm.so:x11/xcb-util-wm \
				libxcb-keysyms.so:x11/xcb-util-keysyms \
				libxcb-util.so:x11/xcb-util

USES=			gmake pkgconfig xorg
USE_XORG=		x11 xcb
MAKE_ARGS=		MANPREFIX="${PREFIX}/man"

PLIST_FILES=	bin/frankenwm \
				man/man1/frankenwm.1.gz

.include <bsd.port.mk>
