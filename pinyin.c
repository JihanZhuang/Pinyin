//pinyin.c
#include "php_pinyin.h"
zend_class_entry *dictLoaderInterface_ce;
zend_class_entry *fileDictLoader_ce;
zend_class_entry *pinyin_ce;

PHP_METHOD(FileDictLoader,__construct){
	zval *path=NULL;
	zval *tmp=getThis();
	if(zend_parse_parameters(ZEND_NUM_ARGS(), "z", &path)==FAILURE){
		return;
	}
	zend_update_property(fileDictLoader_ce, tmp, "path", sizeof("path")-1, path);
}

PHP_METHOD(FileDictLoader,map){
	zval *string;
	zval *path;
	zval *segmentName;
	zval *tmp=getThis();
	zval rv;
	char *segment;
	int i;
	zval file,ret1,ret2,args[2],fname,strFname;
	if(zend_parse_parameters(ZEND_NUM_ARGS(),"z",&string)==FAILURE){
		return;
	}
	path=zend_read_property(fileDictLoader_ce,tmp,"path",sizeof("path")-1,0,&rv);
	segmentName=zend_read_property(fileDictLoader_ce,tmp,"segmentName",sizeof("segmentName")-1,0,&rv);
	//segment=(char *)malloc(path->value.str->len+segmentName->value.str->len+sizeof(char)*5);

	ZVAL_STRING(&fname,"parse_ini_file");
	ZVAL_STRING(&strFname,"strtr");
	for(i=0;i<100;i++){
		spprintf(&segment,0,"%s/%s%d",ZSTR_VAL(Z_STR_P(path)),ZSTR_VAL(Z_STR_P(segmentName)),i);
	//	printf("%s\n",segment);
		if(!access(segment,0)){
		ZVAL_STRING(&file,segment);
		ZVAL_COPY_VALUE(&args[0], &file);
		if(call_user_function(EG(function_table), NULL, &fname, &ret1, 1, args) == SUCCESS){
			zval_ptr_dtor(&args[0]);
			ZVAL_COPY_VALUE(&args[0], string);
			ZVAL_COPY_VALUE(&args[1], &ret1);
			if(call_user_function(EG(function_table),NULL,&strFname,&ret2,2,args)==SUCCESS){
				zval_ptr_dtor(&args[0]);
				zval_ptr_dtor(&args[1]);
				ZVAL_COPY_VALUE(string,&ret2);
			}else{
				php_error_docref(NULL, E_WARNING, "strtr error!");
			}
		}else{
			php_error_docref(NULL, E_WARNING, "can not parse the file %s",segment);
		}
		}
		if(segment){
			efree(segment);
		}
	}
	printf("%s\n",string->value.str->val);
	ZVAL_COPY_VALUE(return_value,string);
	zval_ptr_dtor(&fname);
	zval_ptr_dtor(&strFname);
	zval_ptr_dtor(&rv);
}

PHP_METHOD(FileDictLoader,mapSurname){
	zval *string;
	zval *path;
	zval *tmp=getThis();
	zval rv,dictionary,file;
	zval args[4];
	zval fname,strposF,mbsubstrF,mbstrlenF,encode;
	char *surnames;
	zend_string *surname;
	zval *pinyin;
	zval ret1,ret2,ret3;
	char *str;

	if(zend_parse_parameters(ZEND_NUM_ARGS(),"z",&string)==FAILURE){
		return;
	}
	path=zend_read_property(fileDictLoader_ce,tmp,"path",sizeof("path")-1,0,&rv);

	spprintf(&surnames,0,"%s/surnames",path->value.str->val);
	//printf("%s",surnames);

	ZVAL_STRING(&fname,"parse_ini_file");
	ZVAL_STRING(&strposF,"strpos");
	ZVAL_STRING(&mbsubstrF,"mb_substr");
	ZVAL_STRING(&mbstrlenF,"mb_strlen");
	ZVAL_STRING(&encode,"UTF-8");

	if(!access(surnames,0)){
		ZVAL_STRING(&file,surnames);
		ZVAL_COPY_VALUE(&args[0],&file);
		if(call_user_function(EG(function_table),NULL,&fname,&dictionary,1,args)==SUCCESS){
			zval_ptr_dtor(&args[0]);
			ZEND_HASH_FOREACH_STR_KEY_VAL_IND(Z_ARRVAL(dictionary), surname, pinyin) {
				ZVAL_COPY_VALUE(&args[0],string);
				ZVAL_STR(&args[1],surname);
				if(call_user_function(EG(function_table),NULL,&strposF,&ret1,2,args)==SUCCESS){
					if(Z_LVAL(ret1)==0){
						zval_ptr_dtor(&ret1);
						ZVAL_STR(&args[0],surname);
						ZVAL_COPY(&args[1],&encode);
						if(call_user_function(EG(function_table),NULL,&mbstrlenF,&ret1,2,args)==FAILURE){
							return ;
						}
						ZVAL_COPY_VALUE(&args[0],string);
						if(call_user_function(EG(function_table),NULL,&mbstrlenF,&ret2,2,args)==FAILURE){
							return ;
						}
						ZVAL_COPY_VALUE(&args[1],&ret1);
						Z_LVAL(ret2)--;
						ZVAL_COPY_VALUE(&args[2],&ret2);
						ZVAL_COPY_VALUE(&args[3],&encode);
						if(call_user_function(EG(function_table),NULL,&mbsubstrF,&ret3,4,args)==FAILURE){
			                return ;
						}
						spprintf(&str,0,"%s%s",Z_STRVAL_P(pinyin),Z_STRVAL(ret3));
						break;
					}
				}


			} ZEND_HASH_FOREACH_END();
		}
	}

	ZVAL_STRING(return_value,str);
	if(str){
		efree(str);
	}
	if(surnames){
		efree(surnames);
	}
	zval_ptr_dtor(&file);
	zval_ptr_dtor(&dictionary);
	zval_ptr_dtor(&rv);
	zval_ptr_dtor(&fname);
	zval_ptr_dtor(&strposF);
	zval_ptr_dtor(&mbsubstrF);
	zval_ptr_dtor(&mbstrlenF);
	zval_ptr_dtor(&encode);
	zval_ptr_dtor(&ret1);
	zval_ptr_dtor(&ret2);
	zval_ptr_dtor(&ret3);
	//zval_ptr_dtor(&args[0]);
	zval_ptr_dtor(&args[1]);
	zval_ptr_dtor(&args[2]);
	zval_ptr_dtor(&args[3]);

}

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
PHP_METHOD(Pinyin,prepare){
	char *str=NULL;
	size_t len;
	if(zend_parse_parameters(ZEND_NUM_ARGS(),"s",&str,&len) == FAILURE){
        return;
    }
	//可变长度的字符串是用堆分配内存的，可以修改。
	//str[0]='c';
	//printf("%s",str);
	char *tmp=NULL;
	int i=0;
	int flag=0;
	int j=0;
	int tlen;
	for(;i<len;i++){
		if(((str[i]>='A'&&str[i]<='Z')||(str[i]>='a'&&str[i]<='z')||(str[i]>='0'&&str[i]<='9')||str[i]=='_'||str[i]=='-')&&flag==0){
				flag=1;
				if(tmp==NULL){
					tlen=0;
				}else{
				tlen=strlen(tmp);		
				}
			tmp=(char *)realloc(tmp,tlen+sizeof(char)*(i-j)+strlen("\t")+1);
			strncpy(tmp+tlen,str+j,i-j);
			*(tmp+i-j+tlen)='\0';
			strcat(tmp,"\t");
			j=i;

		}
		if(!((str[i]>='A'&&str[i]<='Z')||(str[i]>='a'&&str[i]<='z')||(str[i]>='0'&&str[i]<='9')||str[i]=='_'||str[i]=='-')&&flag==1){
				flag=0;
		}
	}
	tlen=strlen(tmp);
	tmp=(char *)realloc(tmp,tlen*sizeof(char)+(i-j)*sizeof(char)+1);
	strncpy(tmp+tlen,str+j,i-j+1);
	//printf("%s\n",tmp);
	//ZVAL_STRING(return_value,tmp);
	zval argv[3];
	zval  retval;
	zval fname;
	int   error;
	ZVAL_STRING(&fname,"preg_replace");
	ZVAL_STRING(&argv[0],"~[^\\p{Han}\\p{P}\\p{Z}\\p{M}\\p{N}\\p{L}\\t]~u");
	ZVAL_STRING(&argv[2], tmp);
	ZVAL_STRING(&argv[1],"");
	error=call_user_function(EG(function_table), NULL, &fname, &retval, 3, argv);
	if (error == FAILURE) {
				php_error_docref(NULL, E_WARNING, "Could not call preg_replace in the class of pinyin");
	}else{
		ZVAL_COPY(return_value,&retval);
	}
	zval_ptr_dtor(&fname);
		zval_ptr_dtor(&argv[0]);
		zval_ptr_dtor(&argv[1]);
		zval_ptr_dtor(&argv[2]);
		zval_ptr_dtor(&retval);
	free(tmp);
	//return SUCCESS;


}

PHP_METHOD(Pinyin,format){
	zval *pinyin,*tone=NULL;
	char *searchs[28]={
		"üē","üé","üě","üè",
		"ā","á","ǎ","à",
		"ē","é","ě","è",
		"ī","í","ǐ","ì",
		"ō","ó","ǒ","ò",
		"ū","ú","ǔ","ù",
		"ǖ","ǘ","ǚ","ǜ"
	};
	char *replace[7]={
		"ue","a","e","i","o","u","v"
	};
	int i;
	char *pos;
	char *new_pinyin;


	if(zend_parse_parameters(ZEND_NUM_ARGS(),"z|z",&pinyin,&tone)==FAILURE){
		return ;
	}
		for(i=0;i<28;){
			pos=strstr(ZSTR_VAL(Z_STR_P(pinyin)),searchs[i]);
			if(pos!=NULL){
				if(i<=3){
					ZSTR_VAL(Z_STR_P(pinyin))[pos-ZSTR_VAL(Z_STR_P(pinyin))]=replace[i/4][0];
					ZSTR_VAL(Z_STR_P(pinyin))[pos-ZSTR_VAL(Z_STR_P(pinyin))+1]=replace[i/4][1];
					ZSTR_VAL(Z_STR_P(pinyin))[pos-ZSTR_VAL(Z_STR_P(pinyin))+2]=i%4+1+'0';
					ZSTR_VAL(Z_STR_P(pinyin))[pos-ZSTR_VAL(Z_STR_P(pinyin))+3]=' ';
				}else{
					ZSTR_VAL(Z_STR_P(pinyin))[pos-ZSTR_VAL(Z_STR_P(pinyin))]=replace[i/4][0];
					ZSTR_VAL(Z_STR_P(pinyin))[pos-ZSTR_VAL(Z_STR_P(pinyin))+1]=i%4+1+'0';
				}
			}else{
				i++;
			}
		}
		/*if(tone!=NULL&&Z_TYPE_P(tone)==IS_TRUE){
			spprintf(&new_pinyin,0,"%s%d",ZSTR_VAL(Z_STR_P(pinyin)),i%5+1);
			ZVAL_STRING(return_value,new_pinyin);
			if(new_pinyin){
				efree(new_pinyin);
			}
		}else{*/
			ZVAL_COPY(return_value,pinyin);
		


}

PHP_METHOD(Pinyin,splitWords){
	zval *pinyin,*option;
	zval ret;
	zval fname;
	zval args[2];
	zval split;
	zend_ulong	 num_key;
	zval *subject_entry;
	zval tone;
	zval *pyObj=getThis();

	if(zend_parse_parameters(ZEND_NUM_ARGS(),"zz",&pinyin,&option)==FAILURE){
		return ;
	}
	ZVAL_STRING(&fname,"preg_split");
	ZVAL_STRING(&args[0],"/[^üāēīōūǖáéíóúǘǎěǐǒǔǚàèìòùǜa-z\\d]+/iu");
	ZVAL_COPY_VALUE(&args[1],pinyin);
	if(call_user_function(EG(function_table),NULL,&fname,&ret,2,args)==SUCCESS){
			zval_ptr_dtor(&fname);
			zval_ptr_dtor(&args[0]);
			
			ZVAL_STRING(&fname,"array_filter");
			ZVAL_COPY_VALUE(&args[0],&ret);
			if(call_user_function(EG(function_table),NULL,&fname,&ret,1,args)==SUCCESS){
				ZVAL_COPY_VALUE(&split,&ret);
				zval_ptr_dtor(&args[0]);
				zval_ptr_dtor(&fname);
				if(strcasecmp(ZSTR_VAL(Z_STR_P(option)),"unicode")!=0){
						ZVAL_FALSE(&tone);
						if(strcasecmp(ZSTR_VAL(Z_STR_P(option)),"ascii")==0){
							ZVAL_TRUE(&tone);
						}
						ZVAL_COPY_VALUE(&args[1],&tone);
						ZVAL_STRING(&fname,"format");
						ZEND_HASH_FOREACH_NUM_KEY_VAL(Z_ARRVAL(split), num_key,  subject_entry) {
								ZVAL_COPY_VALUE(&args[0],subject_entry);
								if(call_user_function(EG(function_table),pyObj,&fname,&ret,2,args)==SUCCESS){
									zval tmp;
									ZVAL_COPY(&tmp,&ret);
									zend_hash_index_update(Z_ARRVAL(split),num_key,&tmp);
									zval_ptr_dtor(&ret);
								}
						}ZEND_HASH_FOREACH_END();
						zval_ptr_dtor(&fname);
						ZVAL_STRING(&fname,"array_values");
						ZVAL_COPY_VALUE(&args[0],&split);
						if(call_user_function(EG(function_table),NULL,&fname,&ret,1,args)==SUCCESS){
							ZVAL_COPY(return_value,&ret);
						}
						
				}
			}
			zval_ptr_dtor(&fname);
			zval_ptr_dtor(&ret);

	}else{
		zval_ptr_dtor(&fname);
		zval_ptr_dtor(&args[0]);
		zval_ptr_dtor(&ret);
		return ;
	}

}

PHP_METHOD(Pinyin,sentence){
	zval *punctuations;
	zval *sentence,*withTone;
	zval fname,args[3],rv,ret,*punctuationsRegex;
	zval *pyObj=getThis();
	char *regex;
	zval pinyin,tpunctuations;
	zval tmpArr;

	if(zend_parse_parameters(ZEND_NUM_ARGS(),"z|z",&sentence,&withTone)==FAILURE){
		return;
	}
	//Z_OBJCE_P(objPtr) is a define for you to get the Obj->ce quickly;
	//you can fine zend_class_entry is one of _zend_value's union,and it is equla to zend_object's ce
	punctuations=zend_read_property(Z_OBJCE_P(pyObj),pyObj,"punctuations",sizeof("punctuations")-1,0,&rv);
	
	ZEND_STRING(&fname,"array_keys");
	ZEND_COPY_VALUE(&args[0],punctuations);
	
	if(call_user_function(EG(function_table),NULL,&fname,&ret,1,args)==FAILURE){
		zval_ptr_dtor(&fname);
		zval_ptr_dtor(&ret);
		return;
	}
	zval_ptr_dtor(&fname);
	ZEND_STRING(&fname,"array_merge");
	ZEND_COPY_VALUE(&args[0],&ret);
	ZEND_COPY_VALUE(&args[1],punctuations);
	if(call_user_function(EG(function_table),NULL,&fname,&ret,1,args)==FAILURE){
		zval_ptr_dtor(&fname);
		zval_ptr_dtor(&args[0]);
		zval_ptr_dtor(&ret);
		return;
	}
	zval_ptr_dtor(&fname);
	zval_ptr_dtor(&args[0]);
	ZEND_STRING(&fname,"implode");
	ZEND_COPY_VALUE(&args[0],&ret);
	if(call_user_function(EG(function_table),NULL,&fname,&ret,1,args)==FAILURE){
		zval_ptr_dtor(&fname);
		zval_ptr_dtor(&args[0]);
		zval_ptr_dtor(&ret);
		return;
	}
	zval_ptr_dtor(&fname);
    zval_ptr_dtor(&args[0]);
	ZEND_STRING(&fname,"preg_quote");
	ZEND_COPY_VALUE(&args[0],&ret);
	ZEND_STRING(&args[1],"/");
	if(call_user_function(EG(function_table),NULL,&fname,&ret,2,args)==FAILURE){
		zval_ptr_dtor(&fname);
		zval_ptr_dtor(&args[0]);
		zval_ptr_dtor(&args[1]);
		zval_ptr_dtor(&ret);
		return;
	}
	zval_ptr_dtor(&fname);
	zval_ptr_dtor(&args[0]);
	zval_ptr_dtor(&args[1]);
	punctuationsRegex=&ret;
	spprintf(&regex,0,"/[^üāēīōūǖáéíóúǘǎěǐǒǔǚàèìòùǜa-z0-9%s\\s_]+/iu",ZSTR_VAL(Z_STR_P(punctuationsRegex)));
	zval_ptr_dtor(&ret);
	ZVAL_STRING(&fname,"romanize");
	ZEND_COPY_VALUE(&args[0],sentence);
	if(call_user_function(EG(function_table),pyObj,&fname,&ret,1,args)==FAILURE){
		zval_ptr_dtor(&fname);
		zval_ptr_dtor(&ret);
		return;
	}
	zval_ptr_dtor(&fname);
	ZEND_STRING(&fname,"preg_replace");
	ZVAL_STRING(&args[0],regex);
	ZVAL_STRING(&args[1],"");
	if(regex){
		efree(regex);
	}
	ZVAL_COPY_VALUE(&args[2],&ret);
	if(call_user_function(EG(function_table),NULL,&fname,&ret,3,args)==FAILURE){
		zval_ptr_dtor(&fname);
		zval_ptr_dtor(&args[0]);
		zval_ptr_dtor(&args[1]);
		zval_ptr_dtor(&args[2]);
		zval_ptr_dtor(&ret);
		return;
	}
	zval_ptr_dtor(&fname);
	zval_ptr_dtor(&args[0]);
	zval_ptr_dtor(&args[1]);
	zval_ptr_dtor(&args[2]);
	ZVAL_DUP(&pinyin,&ret);//need free
	//pinyin=&ret;//need free pinyin
	ZEND_STRING(&fname,"array_merge");
	init_array(&tmpArr);
	add_assoc_string(&tmpArr,"\t"," ");
	add_assoc_string(&tmpArr,"  "," ");
	ZEND_COPY_VALUE(&args[0],punctuations);
	ZEND_COPY_VALUE(&args[1],&tmpArr);
	call_user_function(EG(function_table),NULL,&fname,&ret,2,args);
		zval_ptr_dtor(&fname);
		zval_ptr_dtor(&args[1]);
	ZVAL_DUP(&tpunctuations,&ret);//need free
	zval_ptr_dtor(&ret);
	ZVAL_STRING(&fname,"array_keys");
	ZEND_COPY_VALUE(&args[0],tpunctuations);
	call_user_function(EG(function_table),NULL,&fname,&ret,1,args);
	zval_ptr_dtor(&fname);
	ZEND_STRING(&fname,"str_replace");
	ZEND_COPY_VALUE(&args[0],&ret);
	ZEND_COPY_VALUE(&args[1],&tpunctuations);
	ZEND_COPY_VALUE(&args[2],&pinyin);
	call_user_function(EG(function_table),NULL,&fname,&ret,3,args);
	zval_ptr_dtor(&fname);
	zval_ptr_dtor(&args[0]);
	zval_ptr_dtor(&args[1]);
	zval_ptr_dtor(&args[2]);
	
	//ret equals pinyin
	if(Z_TYPE_P(withTone)==IS_TRUE){
		ZEND_COPY_VALUE(return_value,&ret);
	}else{
		ZVAL_STRING(&fname,"format");
		ZEND_COPY_VALUE(&args[1],&ret);
		ZVAL_BOOL(&args[1],0);
		call_user_function(EG(function_table),pyObj,&fname,&ret,2,args);
		ZEND_COPY_VALUE(return_value,&ret);

	}
}

ZEND_BEGIN_ARG_INFO_EX(arginfo_Pinyin___construct, 0, 0, 1)
		//ZEND_ARG_OBJ_INFO(0, loader,"DictLoaderInterface",1)
		ZEND_ARG_TYPE_INFO(0,loader,IS_STRING,1)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO(arginfo_Pinyin_prepare, 0)
		ZEND_ARG_INFO(0,str)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO(arginfo_Pinyin_format,0)
		ZEND_ARG_INFO(0,pinyin)
		ZEND_ARG_INFO(0,tone)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO(arginfo_Pinyin_splitWords,0)
		ZEND_ARG_INFO(0,pinyin)
		ZEND_ARG_INFO(0,option)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO(arginfo_Pinyin_sentence,0)
		ZEND_ARG_INFO(0,sentence)
		ZEND_ARG_INFO(0,withTone)
ZEND_END_ARG_INFO()
const zend_function_entry pinyin_method[]={
	PHP_ME(Pinyin,		__construct,    arginfo_Pinyin___construct,   ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
	PHP_ME(Pinyin,		prepare, arginfo_Pinyin_prepare,	ZEND_ACC_PUBLIC)
	PHP_ME(Pinyin,		format,	arginfo_Pinyin_format,		ZEND_ACC_PUBLIC)
	PHP_ME(Pinyin,		splitWords,arginfo_Pinyin_splitWords,		ZEND_ACC_PUBLIC)
	PHP_ME(Pinyin,		sentence,arginfo_Pinyin_sentence,		ZEND_ACC_PUBLIC)
    {NULL,NULL,NULL}
};
ZEND_BEGIN_ARG_INFO_EX(arginfo_DictLoaderInterface_map, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, string,IS_STRING,1)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO_EX(arginfo_DictLoaderInterface_mapSurname, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, string,IS_STRING,1)
ZEND_END_ARG_INFO()	

const zend_function_entry dictLoaderInterface_method[]={
	PHP_ABSTRACT_ME(DictLoaderInterface, map, arginfo_DictLoaderInterface_map)
	PHP_ABSTRACT_ME(DictLoaderInterface, mapSurname, arginfo_DictLoaderInterface_mapSurname)
	{NULL,NULL,NULL}
};

ZEND_BEGIN_ARG_INFO_EX(arginfo_FileDictLoader___construct, 0, 0, 1)
    ZEND_ARG_INFO(0, path)
ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO_EX(arginfo_FileDictLoader_map, 0, 0, 1)
    ZEND_ARG_TYPE_INFO(0, string,IS_STRING,1)
	ZEND_END_ARG_INFO()
ZEND_BEGIN_ARG_INFO_EX(arginfo_FileDictLoader_mapSurname, 0, 0, 1)
    ZEND_ARG_TYPE_INFO(0, string,IS_STRING,1)
ZEND_END_ARG_INFO()

const zend_function_entry fileDictLoader_method[]={
	PHP_ME(FileDictLoader,      __construct,    arginfo_FileDictLoader___construct,   ZEND_ACC_PUBLIC|ZEND_ACC_CTOR)
    PHP_ME(FileDictLoader,      map, arginfo_FileDictLoader_map,    ZEND_ACC_PUBLIC)
	PHP_ME(FileDictLoader,      mapSurname, arginfo_FileDictLoader_mapSurname,    ZEND_ACC_PUBLIC)
    {NULL,NULL,NULL}
};

PHP_MINIT_FUNCTION(pinyin)
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
	
    INIT_CLASS_ENTRY(ce,"DictLoaderInterface",dictLoaderInterface_method);
	dictLoaderInterface_ce= zend_register_internal_interface(&ce);

	INIT_CLASS_ENTRY(ce,"FileDictLoader",fileDictLoader_method);
	fileDictLoader_ce= zend_register_internal_class(&ce);
	zend_class_implements(fileDictLoader_ce, 1, dictLoaderInterface_ce);
	zend_declare_property_null(fileDictLoader_ce, "path", strlen("path"), ZEND_ACC_PROTECTED);
	zend_declare_property_string(fileDictLoader_ce, "segmentName", strlen("segmentName"),"words_", ZEND_ACC_PROTECTED);
		
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
