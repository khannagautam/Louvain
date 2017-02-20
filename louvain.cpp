/* Implementation 6 of BiLouvain Method dated 20.02.2017
   Author: Gautam Khanna  */

#include<bits/stdc++.h>
using namespace std;

//defining a community
struct cluster
{
	vector<int> vert;
	//list of vertices in the community
	int blue,red,self;
	
	//to store the degree of red and blue and self loops of the community
	bool single;
};

/*Input format : 1. Enter number of vertices and edges
				 2. Enter the colour of n vertices. 1- red, 2-blue
				 3. Enter the edge list(0-indexed)
				 
*/

/* Please note that the code assumes all the vertices in the edge list should lie between 0 and n-1*/


//trying something close to path compression
int getParent(int v,vector<int>& parent)
{
	//returns id of the parent cluster
	if(parent[v]==v)
	  return v;
	
	return parent[v]=getParent(parent[v],parent);
}


int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int n,m,i,j,a,b;
	cin>>n>>m;
	
	
	//n- number of vertices in the graph
	//m- the number of edges in the graph
	
	
	map<int, map<int,pair<int,int> > >adj;//map of map of pairs to store the adjacency list
	//first: red edges from i-j, second: blue edges from i-j
	
	map<int,cluster> track;//map to store the active clusters
	
	vector<int> parent(n);//vector storing the id which is the supernode of that cluster
	
	vector<int> colour(n);
	int c=0;//stores the colour entered by user
	
	/* Taking the colours of the n vertices as input
	   1 if it is red, 0 otherwise*/
	/*creating and initializing n communities*/
	for(i=0;i<n;i++)
	{
		cin>>c;
		colour[i]=c;
		cluster cl;
		cl.vert.resize(0);
		cl.red=cl.blue=0;
		
		parent[i]=i;// initial parent is the node itself
		cl.red=cl.blue=cl.self=0;  
		cl.vert.push_back(i);
		cl.single=true;
		track[i]=cl;//storing the community
	}
	cluster c1,c2;
	//taking the edge list as input
	for(i=0;i<m;i++)
	{
		cin>>a>>b;
		c1=track[a];
		c2=track[b];
		if(colour[a])
		{
			adj[a][b].first++;
			adj[b][a].second++;
			c1.red++;
			c2.blue++;
		}
		else
		{
			
			adj[a][b].second++;
			adj[b][a].first++;
			c2.red++;
			c1.blue++;
		}
	//	cout<<a<<" "<<b<<" "<<c1.red<<" "<<c1.blue<<" "<<c2.red<<" "<<c2.blue<<" "<<adj[a][b].first<<" "<<adj[a][b].second<<endl;
			track[a]=c1;
			track[b]=c2;
	}
	double modularity=0;
	int pass=1;
	
	cout<<"Pass 0: "<<modularity<<endl;
	bool flag=true;//flag to indicate a positive value of del Q for each pass
	while(flag)
	{
		
		flag=false;//set flag as false for each pass
		for(map<int,map<int,pair<int,int> > >::iterator it=adj.begin();it!=adj.end();it++)
		{
			
			i=it->first;//index of the cluster we are on
			map<int,int> done;//indicates the clusters which have been visited for a particular index
			double maxmod=-1;//maximum modularity initialized with -1
			int pos=-1;//position where maximum modularity is obtained
			double mod;//modularity for a neighbour
			cluster c1=track[i];//present community
		
			/* Going through all the neighbours of cluster i and finding the modularity value*/		
			for(map<int,pair<int,int> >::iterator j=adj[i].begin();j!=adj[i].end();j++)
			{
				
				int p=getParent(j->first,parent);
			 	//p- parent id of the community
			
			
				//if neighbour part of the same cluster
				if(p==i) 
			 		continue;
			 		
			 	
			 	//if neighbour's community has already been visited
				if(done[p]>0)
			 		continue;
			
				
			 	done[p]++;//updating the done map so that this cluster is not repeated again
				
				int deg= adj[i][p].first+adj[i][p].second;
				//deg= weight of edge between i and p
				
				cluster c2;
				c2=track[p];
				//neighbouring community
				
				if(c1.single && c2.single)
				{
					//merge singletons. CASE 1
					if(c1.red==0)
					{
						//vertex is blue
						mod= m-(c1.blue*c2.red);
						mod/=(m*m);
					}	
					else
					{
						//vertex is red
						mod= m-(c2.blue*c1.red);
						mod*=1.0;
						mod/=(m*m);
					}
				
				}	
				else if(c1.single)
				{
					//singleton and cluster. CASE 2a
					if(c1.blue==0)
					{
						mod= (deg*1.0/m)-((c1.red*1.0*c2.blue)/(m*m));
					}
					else
					{
						mod=(deg*1.0/m)-((c2.red*1.0*c1.blue)/(m*m));
					}
				}	
				else if(c2.single)
				{
					//singleton and cluster. CASE 2b
					if(c2.red==0)
					{
						mod= (deg*1.0/m)-((c1.red*1.0*c2.blue)/(m*m));
					}
					else
					{
						mod=(deg*1.0/m)-((c2.red*1.0*c1.blue)/(m*m));
					}
				}
				else
				{
					//cluster and cluster. CASE 3
					mod= (deg*1.0/m)-((c1.red*1.0*c2.blue)/(m*m))-((c2.red*1.0*c1.blue)/(m*m));
				
				}
			
				if(mod>maxmod)
				{
					maxmod=mod;
					pos=p;
				}
			
		}
	//	cout<<i<<" "<<pos<<" "<<maxmod<<" "<<endl;
	
		/* if maximum possible del Q obtained is positive merging the two clusters*/
		if(maxmod>0 && i!=pos)
		{
			flag=true;//shows work is done in this pass
			modularity+=maxmod;
			cluster c2=track[pos];
			//updating cluster 1
			c1.single=false;
			c1.red+=c2.red-adj[i][pos].first;
			c1.blue+=c2.blue-adj[i][pos].second;
			c1.self+=c2.self+adj[i][pos].first+adj[i][pos].second;
			parent[pos]=i;
			for(int kk=0;kk<c2.vert.size();kk++)
			{
				c1.vert.push_back(c2.vert[kk]);
			}
			//updating adjacency list: weight of edges from new cluster will include the previous weights of cluster 2
			for(map<int,pair<int,int> >:: iterator kk=adj[pos].begin();kk!=adj[pos].end();kk++)
			{
				adj[i][kk->first].first+=kk->second.first;
				adj[i][kk->first].second+=kk->second.second;
			}
			track[i]=c1;
			adj.erase(pos);
			track.erase(pos);
			
		}
	}
	
	cout<<"Pass "<<pass<<": "<<modularity<<endl;
	pass++;
 }
 
 vector<int> cover(n,0);
 
 /*printing the vertices present in the final clusters after the algo has run, line by line*/
 	for(map<int,cluster >::iterator it=track.begin();it!=track.end();it++)
	{
		i=it->first;
		cluster c=track[i];
		for(j=0;j<c.vert.size();j++)
		  cover[c.vert[j]]=i;
		
	}
	for(i=0;i<n;i++)
	  cout<<i<<" "<<cover[i]<<endl;
	
	for(map<int,cluster >::iterator it=track.begin();it!=track.end();it++)
	{
		i=it->first;
		cluster c=track[i];
		int rctr,bctr;
		rctr=bctr=0;
		cout<<"Cluster "<<i<<": "<<endl;
		cout<<"Vertices in this cluster :"<<endl;
		for(j=0;j<c.vert.size();j++)
		{
			if(colour[c.vert[j]]==1)
			{
				cout<<c.vert[j]<<"-> Red"<<endl;
				rctr++;
			}
			else
			{
				
				cout<<c.vert[j]<<"-> Blue"<<endl;
				bctr++;
			}
			
		}
		double dens= c.self*1.0;
		if(rctr==0 || bctr==0)
		  dens=0;
		else
		dens/=(rctr*bctr);
		cout<<"Edge density of this cluster = "<<dens<<endl;
		cout<<endl<<endl;
	}

}
	
