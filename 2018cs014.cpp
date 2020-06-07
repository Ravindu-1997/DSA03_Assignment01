#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
using namespace std;
#define d 256

void naive(int t, int p, string text, string patt)
{
	ofstream outFile;
	outFile.open("results.txt"); 
	outFile << "Birthday = 970205\n";
	outFile << "Naive string matching\n";

	
	int i,j;
	for(i=0;i<=t-p;i++)
	{
		j=0;
		while(j<p && text[i+j]==patt[j]){
			j++;
			if(j==p)
				outFile << i << "\n";
		}
			
		
	}
	outFile << "\n";

}

void genlps(string patt,int p, int piar[])
{
	int len = 0;
	piar[0] = 0;
	int i = 1;
	
	while(i<p)
	{
		if(patt[i] == patt[len])
		{
			len++;
			piar[i] = len;
			i++;
		}
		else
		{
			if(len!=0)
			{
				len = piar[len-1];
			}
			else
			{
				piar[i] = 0;
				i++;
			}
		}
	}

}

void kmp(int t, int p, string text, string patt)
{
	ofstream outFile;
	outFile.open("results.txt",ios::app);
	outFile << "Birthday = 970205\n";
	outFile << "KMP string matching\n";
	int piar[p];
	genlps(patt,p,piar);
	
	int i = 0;
	int j = 0;
	
	while(i<t)
	{
		if(patt[j] == text[i])
		{
			j++;
			i++;
		}
		if(j == p)
		{
			outFile << i-j << "\n";
			j=piar[j-1];
		}
		else if(i<t && patt[j]!=text[i])
		{
			if(j!=0)
			{
				j = piar[j-1];
			}
			else
			{
				i = i + 1;
			}
		}
	}
	outFile<<"\n";
}




void rabin(int t, int p, string text, string patt)
{
	ofstream outFile;
	outFile.open("results.txt",ios::app);
	outFile << "Rabin-Karp string matching\n";
 	int i,j;
 	int hashpat = 0;
 	int hashtext = 0;
 	int h = 1;
 	int prime = 3;
 	
 	for(i=0;i<p-1;i++)
 	{
 		h = (h*d)%prime;
	}
	for(i=0;i<p;i++)
	{
		hashpat = (d*hashpat + patt[i])%prime;
		hashtext = (d*hashtext + text[i])%prime;
	}
	for(i=0;i<=t-p;i++)
	{
		if(hashpat == hashtext)
		{
			for(j=0;j<p;j++)
			{
				if(text[i+j]!=patt[j])
				break;
			}
			if(j==p)
			{
				outFile<<i<<"\n";
			}
		}
		if(i<t-p)
		{
			hashtext = (d*(hashtext - text[i]*h) + text[i+p])%prime;
			if(hashtext<0)
				hashtext = (hashtext + prime);	
		}	
	}
	outFile<<"\n";
}

void badchartable(string patt, int p, int badchar[d])
{
	int i;
	for(i=0;i<d;i++)
	{
		badchar[i]=-1;
	}
	for(i=0;i<p;i++)
	{
		badchar[(int)patt[i]]=i;
	}
}

int maxi(int x,int y)
{
	return (x>y)? x:y;
}


void boyer(int t, int p, string text,string patt)
{
	ofstream outFile;
	outFile.open("results.txt",ios::app); 
	outFile << "Boyer moore string matching\n";
	int badchar[d];
	badchartable(patt,p,badchar);
	
	int s =0;
	
	while(s<=(t-p))
	{
		int j = p-1;
		
		while(j>=0 && patt[j]==text[s+j])
		j--;
		
		if(j<0)
		{
			outFile<<s<<"\n";
			s+=(s+p<t)?p-badchar[text[s+p]]:1;
		}
		else
		{
			s += maxi(1, j - badchar[text[s+j]]);
		}
	}
	
	outFile<<"\n";
	
}

int main()
{	
	string readLine,block;
    string txt = "";
    string pat = "141592";
    int i=0;

    ifstream dataFile;
    dataFile.open("pi.txt");

    while(getline(dataFile , readLine)){
        if(readLine == "Pi = 3.")
            break;
    }

    while(getline(dataFile,readLine)){
        if(readLine.length() != 0){    
            stringstream ss(readLine);
            for(i=0; i<5; i++){
                ss >> block;
		        txt.append(block);
            }  
        }
    }
    int t = txt.size();
    int p = pat.size();
    
    naive(t,p,txt,pat);
	kmp(t,p,txt,pat);
	rabin(t,p,txt,pat);
	boyer(t,p,txt,pat);
	
}


