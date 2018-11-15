/* Implementation 7 of BiLouvain Method dated 20.04.2017
   Author: Gautam Khanna and Mohit Baid */


/*Input format : 1. Enter number of vertices and edges
		 2. Enter the edge list(0-indexed)
		 3. 1 if you want the code to read the label names from "label.txt", 0 otherwise
*/

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

void bfs(vector<int>& colour,vector< vector<int> >& edge_list,int n)
{
	bool visited[n];
	int i;
	for(i=0;i<n;i++)
	{
		visited[i]=false;
		colour[i]=-1;	
	}
	   
	for(i=0;i<n;i++)
	{
		if(edge_list[i].size()>0)
		  break;
	}
	queue<int> q;
	q.push(i);
	int v;
	while(!q.empty())
	{
		v=q.front();
		q.pop();
		if(colour[v]==-1)
		  colour[v]=0;
		visited[v]=true;
		for(i=0;i<edge_list[v].size();i++)
		{
			if(!visited[edge_list[v][i]])
			{
				 q.push(edge_list[v][i]);
				 colour[edge_list[v][i]]=(colour[v]^1);	
			}
			 
		}
		
	}
	
}


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
	freopen("edge_list.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int n,m,i,j,a,b,fl,w;
	cin>>n>>m;


	//n- number of vertices in the graph
	//m- the number of edges in the graph


	map<int, map<int,pair<int,int> > >adj;//unordered_map of unordered_map of pairs to store the adjacency list
	//first: red edges from i-j, second: blue edges from i-j

	map<int,cluster> track;//unordered_map to store the active clusters

	vector<int> parent(n);//vector storing the id which is the supernode of that cluster
	string label[n];		//for cluster labels
	//cout << "\nn = " << n << endl;
	vector<int> colour(n,-1);
	vector<int> neigh(n,-1);
	// int c=0;//stores the colour entered by user

	/*creating and initializing n communities*/
	for(i=0;i<n;i++)
	{
		colour[i]=-1;
		cluster cl;
		cl.vert.resize(0);
		parent[i]=i;// initial parent is the node itself
		cl.red=cl.blue=cl.self=0;
		cl.vert.push_back(i);
		cl.single=true;
		track[i]=cl;//storing the community
	}
	cluster c1,c2;
	//taking the edge list as input
	vector<vector<int> >edge_list(n);
	vector<pair<int,int> >in;
	vector<int>weights(m,0);
	for(i=0;i<m;i++)
	{
		cin>>a>>b;//>>w;
		edge_list[a].push_back(b);
		edge_list[b].push_back(a);
		weights[i]=1;
		in.push_back(make_pair(a,b));
		//cout<<a<<" "<<endl;
	}
	bfs(colour,edge_list,n);
	for(i=0;i<n;i++)	cout<<colour[i]<<" ";	cout<<endl;
	
	for(i=0;i<m;i++)
	{
		a=in[i].first;
		b=in[i].second;
		w=weights[i];
		c1=track[a];
		c2=track[b];
		if(colour[a])
		{
			adj[a][b].first+=w;
			adj[b][a].second+=w;
			c1.red+=w;
			c2.blue+=w;
		}
		else
		{

			adj[a][b].second+=w;
			adj[b][a].first+=w;
			c2.red+=w;
			c1.blue+=w;
		}
	//	cout<<a<<" "<<b<<" "<<c1.red<<" "<<c1.blue<<" "<<c2.red<<" "<<c2.blue<<" "<<adj[a][b].first<<" "<<adj[a][b].second<<endl;
			track[a]=c1;
			track[b]=c2;
	}
	double modularity=0;
	int pass=1;

	// cout<<"Enter 1 to give node labels, else press any other number\n";
	// cin>>fl;	// 1 To indicate node labels available 
	fl = 0;
	if(fl==1)		
	{
			freopen("label.txt","r",stdin);
			for(i=0;i<n;i++)
			{
				cin>>label[i];
				cout << "label: " << label[i] << endl;
			}
	}


	cout<<"Pass 0: "<<modularity<<endl;
	vector<double> maxmod(n);
	bool flag=true;//flag to indicate a positive value of del Q for each pass
	while(true)
	{
		cerr<<"jijij\n";
		flag=false;//set flag as false for each pass
		double modu=0;
		for(map<int,map<int,pair<int,int> > >::iterator it=adj.begin();it!=adj.end();it++)
		{

			i=it->first;//index of the cluster we are on
			//unordered_map<int,int> done;//indicates the clusters which have been visited for a particular index
			maxmod[i]=-1;//maximum modularity initialized with -1
			int pos=-1;//position where maximum modularity is obtained
			double mod;//modularity for a neighbour
			cluster c1=track[i];//present community
			neigh[i]=i;
			/* Going through all the neighbours of cluster i and finding the modularity value*/
			for(map<int,pair<int,int> >::iterator j=adj[i].begin();j!=adj[i].end();j++)
			{

				int p=getParent(j->first,parent);
			 	//p- parent id of the community


				//if neighbour part of the same cluster
				if(p==i)
			 		continue;

				// 	cerr<<"Red degree: "<<c1.red<<"\n Blue degree: "<<c1.blue<<"\n";

			// cerr<<"Red degree: "<<c2.red<<"\n Blue degree: "<<c2.blue<<"\n";
			// cerr<<"Red* Blue= "<<c1.red*c2.blue<<"\n edge sqaure "<<m*m<<"\n";
			 	//if neighbour's community has already been visited
			//	if(done[p]>0)
			 //		continue;


			 //	done[p]++;//updating the done unordered_map so that this cluster is not repeated again

				int deg= adj[i][p].first+adj[i][p].second;
				//deg= weight of edge between i and p

				cluster c2;
				c2=track[p];
				//neighbouring community
				int pro;
				if(c1.single && c2.single)
				{
					//merge singletons. CASE 1
					if(c1.red==0)
					{
						//vertex is blue
						mod= c1.blue*1.0/m;
						mod *= c2.red*1.0/m;
						mod=(1.0/m)-mod;
					}
					else
					{
						//vertex is red
						mod= c2.blue*1.0/m;
						mod *= c1.red*1.0/m;
						mod=(1.0/m)-mod;

					}

				}
				else if(c1.single)
				{
					//singleton and cluster. CASE 2a
					if(c1.blue==0)
					{
						mod= c2.blue*1.0/m;
						mod *= c1.red*1.0/m;
						mod= (deg*1.0/m)-mod;
					}
					else
					{
						//mod=(deg*1.0/m)-((c2.red*1.0*c1.blue)/(m*m));
						mod= c1.blue*1.0/m;
						mod *= c2.red*1.0/m;
						mod= (deg*1.0/m)-mod;					
					}
				}	
				else if(c2.single)
				{
					//singleton and cluster. CASE 2b
					if(c2.red==0)
					{
						mod= c2.blue*1.0/m;
						mod *= c1.red*1.0/m;
						mod= (deg*1.0/m)-mod;
						//mod= (deg*1.0/m)-((c1.red*1.0*c2.blue)/(m*m));
					}
					else
					{
						mod= c1.blue*1.0/m;
						mod *= c2.red*1.0/m;
						mod= (deg*1.0/m)-mod;	
						//mod=(deg*1.0/m)-((c2.red*1.0*c1.blue)/(m*m));
					}
				}
				else
				{
					//cluster and cluster. CASE 3
					double div1;
					mod= c2.blue*1.0/m;
					mod *= c1.red*1.0/m;
					
					div1= c1.blue*1.0/m;
					div1 *= c2.red*1.0/m;
					
					mod= (deg*1.0/m)-div1-mod;
					//mod= (deg*1.0/m)-((c1.red*1.0*c2.blue)/(m*m))-((c2.red*1.0*c1.blue)/(m*m));

				}

				if(mod>maxmod[i])
				{
					maxmod[i]=mod;
					pos=p;
					neigh[i] = p;
				}

			}
		}
		
	//	cout<<i<<" "<<pos<<" "<<maxmod<<" "<<endl;
//		for(i=0;i<n;i++)	cerr<<neigh[i]<<" "<<endl;	cout<<endl;		
		//vector<bool> visited(n,false);
		vector<bool> rem(n,false);
		modu=0;		
		for(i=0;i<n;i++)
		{			
			if(adj.find(i) == adj.end())		continue;
			int pari = getParent(i,parent);		
			int parj = getParent(neigh[i],parent);
			//if(pari == parj)			continue;
			if(maxmod[i]>0.000001)
				{
					int pos=neigh[i];					
					modu+=maxmod[i];
					cluster c1 = track[pari];
					cluster c2=track[parj];
					//updating cluster 1
					
					c1.single=false;
					c1.red+=c2.red-adj[i][pos].first;
					c1.blue+=c2.blue-adj[i][pos].second;
					c1.self+=c2.self+adj[i][pos].first+adj[i][pos].second;
					//cerr<<"merging "<<pari<<" and "<<parj<<endl;
					//cerr<<c1.red<<" "<<c1.blue<<" "<<c1.self<<endl;					
					parent[parj]=i;

					for(int kk=0;kk<c2.vert.size();kk++)
					{
						c1.vert.push_back(c2.vert[kk]);
					}

					//updating adjacency list: weight of edges from new cluster will include the previous weights ofcluster2
					for(map<int,pair<int,int> >:: iterator kk=adj[parj].begin();kk!=adj[parj].end();kk++)
					{
						adj[pari][kk->first].first+=kk->second.first;
						adj[pari][kk->first].second+=kk->second.second;
					}
					track[pari] = c1;
					adj.erase(parj);
					track.erase(parj);
				}
			
		}

	pass++;
	if(modularity<modu)	modularity=modu;
	else			break;
	cout<<"Pass "<<pass<<": "<<modularity<<endl;
	
		
 }
	cerr<<modularity<<endl;
 vector<int> cover(n,0);

 	
/*printing the vertices present in the final clusters after the algo has run, line by line*/
 	for(map<int,cluster >::iterator it=track.begin();it!=track.end();it++)
	{
		i=it->first;
		cluster c=track[i];
		for(j=0;j<c.vert.size();j++)
		  cover[c.vert[j]]=i;

	}

	// Make directory 
	if (system("mkdir clusters") != 0)
	{
		system("rmdir clusters /s");
		system("Y");
		system("mkdir clusters");
	}
	///////////////

	freopen("C:\\Users\\HKD\\Lovain\\clusters\\cover.txt","w",stdout);
	for(i=0;i<n;i++)
	  cout<<i<<" "<<cover[i]<<endl;

	for(map<int,cluster >::iterator it=track.begin();it!=track.end();it++)
	{
		if(colour[it->first]!=-1)
		{
			i=it->first;
			stringstream ss;	
			ss << i;
			string filename = "C:\\Users\\HKD\\Lovain\\clusters\\" + ss.str();
			filename.append(".txt");
			freopen(filename.c_str(),"w",stdout);
			cluster c=track[i];
			int rctr,bctr;
			rctr=bctr=0;
			cout<<"Cluster "<<i<<": "<<endl;
			cout<<"Vertices in this cluster : "<<c.vert.size()<<endl;
			// fl = 1;
			for(j=0;j<c.vert.size();j++)
			{
				if(colour[c.vert[j]]==1)
				{
					cout<<c.vert[j];
					if(fl==1)
						cout<<" "<<label[c.vert[j]]<<" -> Red"<<endl;
					else
						cout<<"-> Red"<<endl;	
					rctr++;
				}
				else if(colour[c.vert[j]]==0)
				{
					
					cout<<c.vert[j];
					if(fl==1)
						cout<<" "<<label[c.vert[j]]<<"-> Blue"<<endl;
					else
						cout<<"-> Blue"<<endl;
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
}
