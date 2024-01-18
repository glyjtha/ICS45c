int char_to_index(char ch){

	if (ch >= 'a' && ch <= 'z') {
        ch = 'A' + (ch - 'a');
    }
    if (ch >= 'A' && ch <= 'Z') {
        return ch - 'A';
    }
    return -1;
}

char index_to_char(int i){
	return 'A' + i;
}

void count(string s, int counts[]){
	for (char c : s) {
        int index = char_to_index(c);
        if (index != -1) {
            counts[index]++;
        }
    }
}

void print_counts(int counts[], int len){
	for(int i=0; i<len; ++i){
		if(counts[i]>0) {
			std::cout << index_to_char(i) << ' ' << counts[i] << std::endl;
		}
	}
}


	
