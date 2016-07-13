//pinyin.c
#include "php_pinyin.h"

zend_class_entry *pinyin_ce;

static zend_function_entry pinyin_method[]={
    {NULL,NULL,NULL}
};

ZEND_MINIT_FUNCTION(pinyin)
{
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce,"Pinyin",pinyin_method);
    pinyin_ce = zend_register_internal_class(&ce TSRMLS_CC);
    return SUCCESS;
}

zend_module_entry pinyin_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
     STANDARD_MODULE_HEADER,
#endif
    "pinyin",
    php_pinyin_functions, /* Functions 这里必须写明你的扩展名的函数，使phpapi支持该扩展的所有函数*/
    NULL, /* MINIT */
    NULL, /* MSHUTDOWN */
    NULL, /* RINIT */
    NULL, /* RSHUTDOWN */
    NULL, /* MINFO */
#if ZEND_MODULE_API_NO >= 20010901
    "0.1",
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_PINYIN
ZEND_GET_MODULE(pinyin)
#endif
