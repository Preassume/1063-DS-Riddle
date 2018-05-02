This function will capitalize all letters in a string.

```cpp
string toupper(string w){
	for(int i = 0; i < w.length(); i++){
		if((int)w[i] >= 97 && (int)w[i] <= 122){
			w[i] = w[i] - 32;
		}
	}
	return w;
}
```
