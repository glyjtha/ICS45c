
int String::strlen(const char *s){
    int length = 0;
    while(s[length] != '\0'){
        length++;
    }
    return length;
}

char* String::strcpy(char* dest, const char* src) {
     int i = 0;
      for ( i = 0; src[i] != '\0'; ++i)  
      {
	    dest[i] = src[i];
      }
      dest[i]  = '\0';
      return dest;
}

char* String::strdup(const char *src){
    int length = strlen(src);
    char* new_str = new char[length + 1]; // +1 for null terminator
    strcpy(new_str, src);
    return new_str;
}
