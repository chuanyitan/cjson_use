#include "parson.h"
#include <stdio.h>
#include <stdlib.h>
 
void test_write(void);
void test_read(void);
void serialization_example(void);

 
int main()
{
    test_write();
    test_read();
    char * p = json_serialize_to_string_pretty(json_parse_file("test.json"));
    printf("%s\n", p);
    free(p);
    return 0;
}


void serialization_example(void) {
    JSON_Value *root_value = json_value_init_object();
    JSON_Object *root_object = json_value_get_object(root_value);
    
    char *serialized_string = NULL;
    json_object_set_string(root_object, "name", "John Smith");
    json_object_set_number(root_object, "age", 25);
    json_object_dotset_string(root_object, "address.city", "Cupertino");
    json_object_dotset_value(root_object, "contact.emails", json_parse_string("[\"email@example.com\",\"email2@example.com\"]"));
    
    serialized_string = json_serialize_to_string_pretty(root_value);
    puts(serialized_string);
    
    json_free_serialized_string(serialized_string);
    json_value_free(root_value);
}


void test_write(void)
{
    JSON_Value *pJsonRoot = json_value_init_object();
    json_object_set_string(json_object(pJsonRoot), "name", "JSON中国");
    json_object_set_string(json_object(pJsonRoot), "url", "http://www.json.org.cn");
    json_object_set_number(json_object(pJsonRoot), "page", 88);
    json_object_set_boolean(json_object(pJsonRoot), "isNonProfit", 1);
    JSON_Value *pJsonSub = json_value_init_object();
    json_object_set_value(json_object(pJsonRoot), "address", pJsonSub);
    json_object_set_string(json_object(pJsonSub), "street", "浙大路38号.");
    json_object_set_string(json_object(pJsonSub), "city", "浙江杭州");
    json_object_set_string(json_object(pJsonSub), "country", "中国");
    pJsonSub = json_value_init_array();
    json_object_set_value(json_object(pJsonRoot), "links", pJsonSub);
    JSON_Value *pJsonSubSub = json_value_init_object();
    json_array_append_value(json_array(pJsonSub), pJsonSubSub);
    json_object_set_string(json_object(pJsonSubSub), "name", "Google");
    json_object_set_string(json_object(pJsonSubSub), "url", "http://www.google.com");
    pJsonSubSub = json_value_init_object();
    json_array_append_value(json_array(pJsonSub), pJsonSubSub);
    json_object_set_string(json_object(pJsonSubSub), "name", "Baidu");
    json_object_set_string(json_object(pJsonSubSub), "url", "http://www.baidu.com");
    pJsonSubSub = json_value_init_object();
    json_array_append_value(json_array(pJsonSub), pJsonSubSub);
    json_object_set_string(json_object(pJsonSubSub), "name", "SoSo");
    json_object_set_string(json_object(pJsonSubSub), "url", "http://www.SoSo.com");
    json_serialize_to_file_pretty(pJsonRoot, "test.json");
    json_value_free(pJsonRoot);
}
 
void test_read(void)
{
    int i;
    JSON_Value *schema = json_parse_string("{\"name\":\"\"}");
    JSON_Value *pJsonRoot = json_parse_file("test.json");
    printf("name:%s\n", json_object_get_string(json_object(pJsonRoot), "name"));
    printf("url:%s\n", json_object_get_string(json_object(pJsonRoot), "url"));
    printf("page:%g\n", json_object_get_number(json_object(pJsonRoot), "page"));
    printf("isNonProfit:%s\n", (json_object_get_number(json_object(pJsonRoot), "page") != 0) ? "true":"false");
    printf("address->street:%s\n", json_object_get_string(json_object_get_object(json_object(pJsonRoot), "address"), "street"));
    printf("address->city:%s\n", json_object_get_string(json_object_get_object(json_object(pJsonRoot), "address"), "city"));
    printf("address->country:%s\n", json_object_get_string(json_object_get_object(json_object(pJsonRoot), "address"), "country"));
    for (i = 0; i < json_array_get_count(json_array(json_object_get_value(json_object(pJsonRoot), "links"))); i++)
    {
        printf("links->[%d]->name:%s\n", i, json_object_get_string(json_array_get_object(json_array(json_object_get_value(json_object(pJsonRoot), "links")), i), "name"));
        printf("links->[%d]->url:%s\n", i, json_object_get_string(json_array_get_object(json_array(json_object_get_value(json_object(pJsonRoot), "links")), i), "url"));
    }
    json_value_free(schema);
    json_value_free(pJsonRoot);
}
————————————————
版权声明：本文为CSDN博主「makeWorks」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/MakeWorks/article/details/70213017


