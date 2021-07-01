#include "parson.h"
#include <stdio.h>
#include <stdlib.h>
 
void test_write(void);
void test_read(void);
 
int main()
{
	    test_write();
	        test_read();
		    char * p = json_serialize_to_string_pretty(json_parse_file("test.json"));
		        printf("%s\n", p);
			    free(p);
			        return 0;
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
	        JSON_Value *schema = json_parse_string("{\"name\":\"12345677\"}");
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
