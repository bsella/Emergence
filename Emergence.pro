    QT_VERSION = $$[QT_VERSION]
    QT_VERSION = $$split(QT_VERSION, ".")
    QT_VER_MAJ = $$member(QT_VERSION, 0)
    QT_VER_MIN = $$member(QT_VERSION, 1)

    lessThan(QT_VER_MAJ, 5) | lessThan(QT_VER_MIN, 7) {
        error(Emergence requires Qt 5.7 or newer but Qt $$[QT_VERSION] was detected.)
    }

include(Emergence.pri)

CONFIG = release
TEMPLATE = subdirs
SUBDIRS = plugins\
          src
