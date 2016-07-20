//pinyin.c
#include "php_pinyin.h"

zend_class_entry *pinyin_ce;


PHP_METHOD(Pinyin,__construct){
	//printf("hello world!");
	//printf("%s\n",__func__);
	zval punctuations;
	zval *loader=NULL;
	zval *tmp;
	tmp=getThis();
	//MAKE_STD_ZVAL(punctuations);
	//init punctuations array
	array_init(&punctuations);
	zend_update_property(pinyin_ce,tmp, "punctuations",sizeof("punctuations"), &punctuations);
	add_assoc_string(&punctuations,"，",",");
	add_assoc_string(&punctuations,"。",".");
	add_assoc_string(&punctuations,"！","!");
	add_assoc_string(&punctuations,"？","?");
	add_assoc_string(&punctuations,"：",":");
	add_assoc_string(&punctuations,"“","\"");
	add_assoc_string(&punctuations,"”","\"");
	add_assoc_string(&punctuations,"‘","'");
	add_assoc_string(&punctuations,"’","'");
   

	//init loader
	zval retval;
	zval fname;
	ZVAL_STRING(&fname,"get_class");
	if (zend_parse_parameters(ZEND_NUM_ARGS(), "|z", &loader) == FAILURE) {
			return;
	}
	if(loader!=NULL){
	//call_user_function(CG(function_table),NULL,&fname,&retval,1,loader);
	//printf("%s\n",retval.value.str.val[1]);
	//if(!strcmp(retval.value.str.val,"DictLoaderInterface")){
	//	zend_throw_exception_ex(pinyin_ce,0,"Pinyin __construct's param must be the class of DictLoaderInterface");
	//}
	zend_update_property(pinyin_ce, tmp, "loader", sizeof("loader")-1, loader);

	}
		//printf("%s\n",retval.value.str);
	//printf("%s\n",(&loader));
	//printf("123");
	 zval_ptr_dtor(&punctuations);
	 zval_ptr_dtor(&fname);
}
PHP_FUNCTION(pinyin_convertStr){
	char *str=NULL;
	size_t len;
	if(zend_parse_parameters(ZEND_NUM_ARGS(),"s",&str,&len) == FAILURE){
        return;
    }
	//可变长度的字符串是用堆分配内存的，可以修改。
	//str[0]='c';
	//printf("%s",str);
	
	//return SUCCESS;


}
PHP_METHOD(Pinyin,prepare){
	char *string;
	zval params[1];
	

	if(zend_parse_parameters(ZEND_NUM_ARGS(),"s",string) == FAILURE){
		return;
	}
	printf("%s",string);

	//call_user_function(EG(function_table), NULL, func, &retval, 2, argv);

}
ZEND_BEGIN_ARG_INFO_EX(arginfo_Pinyin___construct, 0, 0, 1)
		ZEND_ARG_OBJ_INFO(0, loader,"DictLoaderInterface",1)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO(arginfo_pinyin_convertStr, 0)
		ZEND_ARG_INFO(0,str)
ZEND_END_ARG_INFO()
const zend_function_entry pinyin_method[]={
	PHP_ME(Pinyin,		__construct,    arginfo_Pinyin___construct,   ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_FE(pinyin_convertStr, arginfo_pinyin_convertStr)
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
    pinyin_ce = zend_register_internal_class(&ce);

	//printf("pinyin_ce is %p,ce is %p",pinyin_ce,&ce);
	//define const var
    zend_declare_class_constant_string(pinyin_ce, "NONE", strlen("NONE"), "none");
	zend_declare_class_constant_string(pinyin_ce, "ASCII", strlen("ASCII"), "ascii");
	zend_declare_class_constant_string(pinyin_ce, "UNICODE", strlen("UNICODE"), "unicode");

	//define protected var
	//定义属性
	zend_declare_property_null(pinyin_ce, "loader", strlen("loader"), ZEND_ACC_PROTECTED);
	zend_declare_property_null(pinyin_ce, "punctuations", strlen("punctuations"), ZEND_ACC_PROTECTED);
	//zval *punctuations;
	//array_init(punctuations);
	//zend_printf("%d", Z_TYPE_P(&punctuations));
    //add_property_zval_ex(pinyin_ce, "punctuations", strlen("punctuations"), &punctuations);
    //zend_declare_property(pinyin_ce, "punctuations", strlen("punctuations"), punctuations,ZEND_ACC_PROTECTED);
    




    return SUCCESS;
}

/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(pinyin)
{
	//zend_hash_destroy(&pdo_driver_hash);
	//pdo_sqlstate_fini_error_table();
	return SUCCESS;
}
/* }}} */ 

zend_module_entry pinyin_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
     STANDARD_MODULE_HEADER,
#endif
    "pinyin",
    pinyin_method, /* Functions 这里必须写明你的扩展名的函数，使phpapi支持该扩展的所有函数*/
    PHP_MINIT(pinyin), /* MINIT */
    PHP_MSHUTDOWN(pinyin), /* MSHUTDOWN */
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
