//php_pinyin.h
#ifndef PINYIN_H
#define PINYIN_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "stdlib.h"
#include "php.h"
#include "php_ini.h"
#include "zend_exceptions.h"
#include "zend_interfaces.h"
extern zend_module_entry pinyin_module_entry;
#define phpext_pinyin_ptr &pinyin_module_entry

#endif
