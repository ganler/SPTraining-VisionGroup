template<typename Iter,typename T>
bool binary_search(Iter beg,Iter end, T&& val){
	while(beg<=end){
		Iter mid=(beg+end)/2;
		if(*mid==val)
			return true;
		else if(*mid<val)
			beg=mid+1;
		else
			end=mid+1;
	}
	return false;
}
