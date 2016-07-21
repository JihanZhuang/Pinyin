//php_pinyin.h
#ifndef PINYIN_H
#define PINYIN_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "stdlib.h"
#include "php.h"
extern zend_module_entry pinyin_module_entry;
#define phpext_pinyin_ptr &pinyin_module_entry

#endif
