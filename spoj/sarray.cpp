#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

#define max 100010
 
int delta, len, SA[max], iSA[max], val[max], tval[max];
char s[max];
bool cmp(const int& a, const int& b) { return val[a+delta] < val[b+delta]; }

// constroi Suffix Array em O(nlog^2n)
void build_SA()
{
	int i, j;
	for (i=0; i<len; i++) val[i] = s[i];
	for (i=0; i<len; i++) SA[i] = i;
	
	delta = 0;
	sort(SA, SA+len, cmp);
			
	for (delta=1;;delta*=2) {
		bool found = false;
		for (i=0; i<len; i++) {
			for (j=i+1; j<len; j++) if (val[SA[i]] != val[SA[j]]) break;
			if (j > i+1) {
				found = true;
				sort(SA+i, SA+j, cmp);
			}
			i = j - 1;
		}
		
		if (!found) break;
		tval[SA[0]] = 0;
		for (i=1; i<len; i++)
		{
			tval[SA[i]] = tval[SA[i-1]];
			if (val[SA[i]] == val[SA[i-1]] && val[SA[i]+delta] == val[SA[i-1]+delta]);
			else tval[SA[i]]++;
		}
		memcpy(val, tval, len * sizeof(int));
	}
	
	//for (i=0; i<len; i++) iSA[SA[i]] = i;	
}

int main() {
    scanf("%s%n", s, &len); 
    /*gets(s);
    len = strlen(s);*/
    build_SA();
    for (int i = 0; i < len; i++) printf("%d\n", SA[i]);
}
