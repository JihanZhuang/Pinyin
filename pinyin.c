//pinyin.c
#include "php_pinyin.h"

zend_class_entry *pinyin_ce;


PHP_METHOD(Pinyin,__construct){
	printf("hello world!");

}

const zend_function_entry pinyin_method[]={
	ZEND_ME(Pinyin,		__construct,    NULL,   ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    {NULL,NULL,NULL}
};

ZEND_MINIT_FUNCTION(pinyin)
{
	//define a entry
    zend_class_entry ce;
	//printf("ce is %p",&ce);
	//init entry
    INIT_CLASS_ENTRY(ce,"Pinyin",pinyin_method);
    //register entry into zend engine
    pinyin_ce = zend_register_internal_class(&ce TSRMLS_CC);

	//printf("pinyin_ce is %p,ce is %p",pinyin_ce,&ce);
	//define const var
    zend_declare_class_constant_string(pinyin_ce, "NONE", strlen("NONE"), "none" TSRMLS_CC);
	zend_declare_class_constant_string(pinyin_ce, "ASCII", strlen("ASCII"), "ascii" TSRMLS_CC);
	zend_declare_class_constant_string(pinyin_ce, "UNICODE", strlen("UNICODE"), "unicode" TSRMLS_CC);

	//define protected var
	//定义属性
	zend_declare_property_null(pinyin_ce, "loader", strlen("loader"), ZEND_ACC_PUBLIC TSRMLS_CC);
	zval punctuations;
	//MAKE_STD_ZVAL(punctuations);
	zend_printf("%d", Z_TYPE_P(&punctuations));


    return SUCCESS;
}



zend_module_entry pinyin_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
     STANDARD_MODULE_HEADER,
#endif
    "pinyin",
    pinyin_method, /* Functions 这里必须写明你的扩展名的函数，使phpapi支持该扩展的所有函数*/
    PHP_MINIT(pinyin), /* MINIT */
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
