
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

char *String::strncpy(char *dest, const char *src, int n) {
    int i;
    for(i=0; i<n && src[i] != '\0'; ++i){
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return dest;
}

char *String::strcat(char *dest, const char *src) {
    int dest_len = strlen(dest); 
    int i = 0;
    while (src[i] != '\0') {
        dest[dest_len + i] = src[i];
        ++i;
    }
    dest[dest_len + i] = '\0'; // Null-terminate the concatenated string
    return dest;
}

char *String::strncat(char *dest, const char *src, int n) {
    int dest_len = strlen(dest);
    int i;
    for (i = 0; i < n && src[i] != '\0'; i++) {
        dest[dest_len + i] = src[i];
    }
    dest[dest_len + i] = '\0';
    return dest;
}

int String::strcmp(const char *left, const char *right){
    int i = 0;
    while (left[i] == right[i]) {
        if (left[i] == '\0') {
            return 0; // Strings are equal
        }
        ++i;
    }
    return (unsigned char)left[i] - (unsigned char)right[i];
}

int String::strncmp(const char *left, const char *right, int n){
    for (int i = 0; i < n; ++i) {
        if (left[i] == '\0' || right[i] == '\0') {
            return (unsigned char)left[i] - (unsigned char)right[i];
        }

        // If characters differ, return the difference
        if (left[i] != right[i]) {
            return (unsigned char)left[i] - (unsigned char)right[i];
        }
    }
    return 0;
}


void String::reverse_cpy(char *dest, const char *src) {
    int len = strlen(src);
    for (int i = 0; i < len; ++i) {
        dest[len - 1 - i] = src[i];
    }
    dest[len] = '\0';
}

const char *String::strchr(const char *src, char c) {
    while (true) {
        if (*src == c) {
            return src; 
        }
        if (*src == '\0') {
            break; 
        }
        ++src;
    }
    return nullptr; // Character not found
}

const char *String::strstr(const char *haystack, const char *needle) {
    if (*needle == '\0') {
        return haystack; // Empty needle should return the full haystack
    }
    int len = strlen(needle);

    for (const char *p = haystack; *p != '\0'; ++p) {
        // Check if there are enough characters left in haystack
        if (strlen(p) < len) {
            return nullptr; // Not enough characters for needle to fit
        }
        if (*p == needle[0]) {
            if (strncmp(p, needle, len) == 0) {
                return p;
            }
        }
    }
    return nullptr;
}

