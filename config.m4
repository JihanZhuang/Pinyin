dnl $Id$
dnl config.m4 for extension Pinyin

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(Pinyin, for Pinyin support,
dnl Make sure that the comment is aligned:
dnl [  --with-Pinyin             Include Pinyin support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(Pinyin, whether to enable Pinyin support,
[  --enable-Pinyin           Enable Pinyin support])

if test "$PHP_PINYIN" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-Pinyin -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/Pinyin.h"  # you most likely want to change this
  dnl if test -r $PHP_PINYIN/$SEARCH_FOR; then # path given as parameter
  dnl   PINYIN_DIR=$PHP_PINYIN
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for Pinyin files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       PINYIN_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$PINYIN_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the Pinyin distribution])
  dnl fi

  dnl # --with-Pinyin -> add include path
  dnl PHP_ADD_INCLUDE($PINYIN_DIR/include)

  dnl # --with-Pinyin -> check for lib and symbol presence
  dnl LIBNAME=Pinyin # you may want to change this
  dnl LIBSYMBOL=Pinyin # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $PINYIN_DIR/$PHP_LIBDIR, PINYIN_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_PINYINLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong Pinyin lib version or lib not found])
  dnl ],[
  dnl   -L$PINYIN_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(PINYIN_SHARED_LIBADD)

  PHP_NEW_EXTENSION(Pinyin, pinyin.c, $ext_shared)
fi
