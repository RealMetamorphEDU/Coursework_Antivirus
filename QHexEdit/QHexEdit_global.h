#ifndef QHEXEDIT_GLOBAL_H
#define QHEXEDIT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(QHEXEDIT_LIBRARY)
#  define QHEXEDIT_EXPORT Q_DECL_EXPORT
#else
#  define QHEXEDIT_EXPORT Q_DECL_IMPORT
#endif

#endif // QHEXEDIT_GLOBAL_H
