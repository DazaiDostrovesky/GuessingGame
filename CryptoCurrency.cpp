
#include <stdio.h>
#include <curl/curl.h>
#include <iostream>
#include <string>
using namespace std;
// 
size_t OutputFeedback(void* recieved_data, size_t size, size_t chunk_size, string* output) {
size_t  total_size=size*chunk_size;
output->append((char*)recieved_data, total_size)
return total_size

}

int main(){
CURL* curl;





    
}

