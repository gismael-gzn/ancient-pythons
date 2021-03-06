# Generated by h2py from /usr/include/sys/fcntl.h

# Included from standards.h

# Included from sys/types.h

# Included from sgidefs.h
_MIPS_ISA_MIPS1 = 1
_MIPS_ISA_MIPS2 = 2
_MIPS_ISA_MIPS3 = 3
_MIPS_ISA_MIPS4 = 4
_MIPS_SIM_ABI32 = 1
_MIPS_SIM_NABI32 = 2
_MIPS_SIM_ABI64 = 3
P_MYID = (-1)
P_MYHOSTID = (-1)

# Included from sys/bsd_types.h

# Included from sys/mkdev.h
ONBITSMAJOR = 7
ONBITSMINOR = 8
OMAXMAJ = 0x7f
OMAXMIN = 0xff
NBITSMAJOR = 14
NBITSMINOR = 18
MAXMAJ = 0x1ff
MAXMIN = 0x3ffff
OLDDEV = 0
NEWDEV = 1
MKDEV_VER = NEWDEV
def major(dev): return __major(MKDEV_VER, dev)

def minor(dev): return __minor(MKDEV_VER, dev)


# Included from sys/select.h
FD_SETSIZE = 1024
__NBBY = 8

# Included from string.h
NULL = 0L
NBBY = 8
FNDELAY = 0x04
FAPPEND = 0x08
FSYNC = 0x10
FDSYNC = 0x20
FRSYNC = 0x40
FNONBLOCK = 0x80
FASYNC = 0x1000
FLARGEFILE = 0x2000
FNONBLK = FNONBLOCK
FDIRECT = 0x8000
FDIRENT64 = 0x8000
FCREAT = 0x0100
FTRUNC = 0x0200
FEXCL = 0x0400
FNOCTTY = 0x0800
O_RDONLY = 0
O_WRONLY = 1
O_RDWR = 2
O_NDELAY = 0x04
O_APPEND = 0x08
O_SYNC = 0x10
O_DSYNC = 0x20
O_RSYNC = 0x40
O_NONBLOCK = 0x80
O_LARGEFILE = 0x2000
O_DIRECT = 0x8000
O_CREAT = 0x100
O_TRUNC = 0x200
O_EXCL = 0x400
O_NOCTTY = 0x800
F_DUPFD = 0
F_GETFD = 1
F_SETFD = 2
F_GETFL = 3
F_SETFL = 4
F_GETLK = 14
F_SETLK = 6
F_SETLKW = 7
F_CHKFL = 8
F_ALLOCSP = 10
F_FREESP = 11
F_SETBSDLK = 12
F_SETBSDLKW = 13
F_DIOINFO = 30
F_FSGETXATTR = 31
F_FSSETXATTR = 32
F_GETLK64 = 33
F_SETLK64 = 34
F_SETLKW64 = 35
F_ALLOCSP64 = 36
F_FREESP64 = 37
F_GETBMAP = 38
F_FSSETDM = 39
F_RESVSP = 40
F_UNRESVSP = 41
F_RESVSP64 = 42
F_UNRESVSP64 = 43
F_GETBMAPA = 44
F_FSGETXATTRA = 45
F_GETALLLK = 46
F_RSETLK = 20
F_RGETLK = 21
F_RSETLKW = 22
F_GETOWN = 23
F_SETOWN = 24
F_RDLCK = 01
F_WRLCK = 02
F_UNLCK = 03
O_ACCMODE = 3
FD_CLOEXEC = 1
FD_NODUP_FORK = 4
