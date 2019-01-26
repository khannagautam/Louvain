#include<bits/stdc++.h>
using namespace std;
int main()
{
	freopen("input.csv","r",stdin);
	map< pair  < string,string > ,int> mp1,mp2;
	long long int c=0;
	int m=255506,i,flag;
	string s,t,p,u,v,temp;
	getline(cin,temp);
	while(m--)
	{
		getline(cin,temp);
		flag=0;
		for(i=0;temp[i]!='\0';i++)
		{
			if(temp[i]==',')
			{
				flag++;
			}
			else
			{
				if(flag==0)			s+=temp[i];
				else if(flag==1)	t+=temp[i];	
				else if(flag==2)	p+=temp[i];
				else if(flag==3)	u+=temp[i];
				else				v+=temp[i];
			}
			if(temp[i]=='"')
			{
				cout<<"A"<<255506-m<<endl;
				cout<<temp<<endl;
				/*for(int hj=0;hj<=500000000;hj++)
				{
				}*/	
			}
		}
		s=s+'\0';
		t=t+'\0';
		p=p+'\0';
		u=u+'\0';
		v=v+'\0';
		if(mp1.find(make_pair(s,t))==mp1.end())
		{
			mp1[make_pair(s,t)]=c++;
			//cout<<temp<<" "<<255506-m<<endl;;
			//cout<<s<<" "<<t<<" "<<c<<endl;
			/*for(int hj=0;hj<=500000000;hj++)
			{
			}*/
		}
		s.clear();
		t.clear();
		p.clear();
		u.clear();
		v.clear();
		temp.clear();
	}
	//cout<<c<<endl;
	m=255506;
	cin.clear();
	freopen("input.csv","r",stdin);
	getline(cin,temp);
	while(m--)
	{
		getline(cin,temp);
		flag=0;
		for(i=0;temp[i]!='\0';i++)
		{
			if(temp[i]==',')
			{
				flag++;
			}
			else
			{
				if(flag==0)			s+=temp[i];
				else if(flag==1)	t+=temp[i];	
				else if(flag==2)	p+=temp[i];
				else if(flag==3)    u+=temp[i];
				else 				v+=temp[i];
			}
		}
		s=s+'\0';
		t=t+'\0';
		p=p+'\0';
		u=u+'\0';
		v=v+'\0';
		if(mp2.find(make_pair(p,u))==mp2.end())
			mp2[make_pair(p,u)]=c++;
		s.clear();
		t.clear();
		p.clear();
		u.clear();
		v.clear();
		temp.clear();
	}
	//cout<<c<<endl;
	//cout<<"ASD"<<endl;
	m=255506;
	cin.clear();
	freopen("input.csv","r",stdin);
	freopen("edge_list.csv","w",stdout);
	cout<<c<<','<<"255506"<<endl;
	getline(cin,temp);
	while(m--)
	{
		getline(cin,temp);
		flag=0;
		for(i=0;temp[i]!='\0';i++)
		{
			if(temp[i]==',')
			{
				flag++;
			}
			else
			{
				if(flag==0)			s+=temp[i];
				else if(flag==1)	t+=temp[i];	
				else if(flag==2)	p+=temp[i];
				else if(flag==3)	u+=temp[i];
				else 				v+=temp[i];
			}
		}
		s=s+'\0';
		t=t+'\0';
		p=p+'\0';
		u=u+'\0';
		v=v+'\0';
		cout<<mp1[make_pair(s,t)]<<','<<mp2[make_pair(p,u)]<<','<<v<<endl;
		s.clear();
		t.clear();
		p.clear();
		u.clear();
		v.clear();
		temp.clear();
	}
	freopen("hash_list.csv","w",stdout);
	map< pair < string,string > ,int> :: iterator it;
	for(it=mp1.begin();it!=mp1.end();it++)
	{
		cout<<it->first.first<<','<<it->first.second<<','<<it->second<<endl;
	}
	for(it=mp2.begin();it!=mp2.end();it++)
	{
		cout<<it->first.first<<','<<it->first.second<<','<<it->second<<endl;
	}
	
	freopen("label.txt","w",stdout);
	for(it=mp1.begin();it!=mp1.end();it++)
	{
		cout<<it->first.first<<' '<<it->first.second<<' '<<it->second<<endl;
	}
	for(it=mp2.begin();it!=mp2.end();it++)
	{
		cout<<it->first.first<<' '<<it->first.second<<' '<<it->second<<endl;
	}
}
