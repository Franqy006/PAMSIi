#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <chrono>


void wyswietlwynik(int * d, int * p, int v, int a)
{
    int pom=-1;
    for(int i=0;i<v;i++)
    {
        pom=p[i];
        std::cout<<"do wierzcholka \""<<i<<"\" jest "<<d[i]<<" przez ";
        while(pom!=a)
        {
            std::cout<<pom<<", ";
            pom=p[pom];
        }
        std::cout<<pom<<std::endl;
    }
} 
namespace lista
{
class listaInc;
class vertex;
} // namespace lista

// class grapho
// {
//     public:
//     virtual int getDirectDist(int n, int m)=0;
//     //virtual void wyswietlajzlisty(lista::listaInc*, int)=0;
//     virtual void somsiady(int n)=0;
//     virtual int getVnr()=0;
//     virtual lista::vertex* getVertex(int n)=0;
// };
// void dijxtra(grapho *graf, int n)
// {
//     lista::vertex *tabela[n];
// }

namespace lista
{
class graph;
class listaInc;
class vertex;
class edge;
class vertex
{
public:
    int numer=0;
    listaInc *mojesomsiady=nullptr;
    //vertex** tendziwny;
};
class listaInc
{
public:
    listaInc *next = nullptr;
    edge *krawedz=nullptr;

public:
    listaInc(edge *nkraw)
    {
        krawedz = nkraw;
    }
    // ~listaInc()
    // {
    //     listaInc* temp;
    //     while (next!=nullptr)
    //     {
    //         temp=next;
    //         next=next->next;
    //         delete temp;
    //     }
        
    // }

};

class edge
{
public:
    vertex *uno=nullptr;
    vertex *dos=nullptr;
    listaInc *deuno=nullptr;
    listaInc *dedos=nullptr;
    int weight=0;
    //edge** tendziwny;
    //edge()=default;
    edge(vertex *wpocz, vertex *wkon, int waga)
    {
        uno = wpocz;
        dos = wkon;
        weight = waga;

        deuno = new listaInc(this);

        if (uno->mojesomsiady == nullptr)
        {
            uno->mojesomsiady = deuno;
        }
        else
        {
            deuno->next = uno->mojesomsiady;
            uno->mojesomsiady = deuno;
        }

        dedos = new listaInc(this);
        if (dos->mojesomsiady == nullptr)
        {
            dos->mojesomsiady = dedos;
        }
        else
        {
            dedos->next = dos->mojesomsiady;
            dos->mojesomsiady = dedos;
        }
    }
};

class priorq
{
public:
    priorq *next = nullptr;
    int weight = 0;
    lista::vertex *myvertex=nullptr;

public:
   
    void add(lista::vertex *newvertex, int dist)
    {
        priorq *pom=nullptr;
        priorq *pomprev=nullptr;
        pomprev = this;
        pom = this->next;

        priorq *newpriorq = new priorq;
        newpriorq->myvertex = newvertex;
        newpriorq->weight = dist;

        while (pom != nullptr && pom->weight < dist)
        {
            pomprev = pom;
            pom = pom->next;
        }

        if (pom != nullptr && pom->weight >= dist)
            newpriorq->next = pom;
        pomprev->next = newpriorq; // niwc lub koniec

        // if(pom==nullptr)
        // {
        //     this->next=newpriorq;
        // }
        // else
        // {
        //       if(pomprev->weight>dist)
        //     {
        //         newpriorq->next=pomprev;
        //     }
        //     else
        //     {

        //     while(pom->next!=nullptr&&dist>pom->next->weight)
        //     {
        //         pom=pom->next;
        //         pomprev=pomprev->next;
        //     }

        //     std::cout<<"tu";

        //     if(pom->next!=nullptr)
        //     {
        //         newpriorq->next=pom->next;
        //     }

        //     pom->next=newpriorq;

        //     }
        // }
    }
   void takelem(int n)
    {
        priorq *pom=nullptr;
        priorq *pom2 = this;
        pom = this->next;
        while(pom!=nullptr && pom->myvertex->numer!=n)
        {
            pom = pom->next;
            pom2=pom2->next;
        }
    
       
        pom2->next = pom->next;
        delete pom;
    }
    priorq *takefirstelem()
    {
        priorq *pom=nullptr;
        pom = this->next;
        this->next = this->next->next;

        return pom;
    }
    priorq *pop()
    {
        priorq *pom=nullptr;
        pom = this->next;
        this->next = this->next->next;

        return pom;
    }
    void push(priorq* pushed)
    {
        priorq *pom=nullptr;
        priorq *pomprev=nullptr;
        pomprev = this;
        pom = this->next;

        while (pom != nullptr && pom->weight < pushed->weight)
        {
            pomprev = pom;
            pom = pom->next;
        }

        if (pom != nullptr && pom->weight >= pushed->weight)
            pushed->next=pom;
        pomprev->next=pushed;


    }
    void wyswietl()
    {
        priorq *pom = this->next;
        //pom=pom->next;
        std::cout << "wyswitlam\n";

        while (pom != nullptr)
        {
            std::cout << "nr: " << pom->myvertex->numer << " dist: " << pom->weight << std::endl;
            pom = pom->next;
        }
    }
};

void wyswietlKolejke(priorq* head)
    {
        priorq* tempq=nullptr;
        priorq* tempq2=nullptr;
        tempq=head;
        tempq=tempq->next;
        while(tempq!=nullptr)
        {
            std::cout<<" numer: "<<tempq->myvertex->numer<<" o wadze"<<tempq->weight<<"\n";
            tempq=tempq->next;
        }
        std::cout<<"\n";

    }

class graph 
{
public:
    int V=0;
    int E=0;
    vertex *wierholki=nullptr;
    edge **krawedzie=nullptr;
    int jebanylicznik=0;

    ~graph()
    {
        listaInc* temp;
        for(int i=0;i<E;i++)
        {
            delete krawedzie[i];
        }
        for(int i=0;i<V;i++)
        {
            temp = wierholki[i].mojesomsiady->next;
			while ( temp!= nullptr)
			{
                wierholki[i].mojesomsiady->next=temp->next;
                delete temp;
                temp=temp = wierholki[i].mojesomsiady->next;

	
			}
			delete wierholki[i].mojesomsiady;
        }
        delete[] krawedzie;
        delete[] wierholki;
    }
    int getVnr()
    {
        return V;
    }

    vertex *getVertex(int n)
    {
        return &(wierholki[n]);
    }
    
    void addEdge(int a, int x, int y, int weight)
    {
        krawedzie[a]=new edge(&wierholki[x],&wierholki[y],weight);
        jebanylicznik++;
    }

    void wyswietlajzlisty(listaInc *wsknaliste, int n)
    {

        if (wsknaliste->krawedz->deuno == wsknaliste)
            std::cout << wsknaliste->krawedz->dos->numer << " ";
        else
        {
            std::cout << wsknaliste->krawedz->uno->numer << " ";
        }

        if (wsknaliste->next == nullptr)
        {
            return;
        }
        wyswietlajzlisty(wsknaliste->next, n);
    }

    void somsiady(int n)
    {
        if (wierholki[n].mojesomsiady == nullptr)
        {
            std::cout << "nimomsomsiadow\n";
            return;
        }
        std::cout << "sasiedzi " << n << " to: ";
        wyswietlajzlisty(wierholki[n].mojesomsiady, n);

        std::cout << std::endl;
    };

    void readGraph(std::string nazwa)
    {
        std::ifstream plik(nazwa);
        int odczyt;
        int wpocz;
        int wkon;
        int waga;
        int i = 0;
        int wstartowy;
        if (plik.is_open() == true)
        {
            plik >> wpocz;
            plik >> wkon;
            makeGraph(wpocz,wkon);
            

            
            plik >> odczyt;
            wstartowy = odczyt;
            while (plik >> odczyt)
            {
                //std::cout<<odczyt;
                wpocz = odczyt;
                plik >> odczyt;
                wkon = odczyt;
                plik >> odczyt;
                waga = odczyt;
                addEdge(i,wpocz, wkon, waga);
                i++;
                //std::cout<<"ELOOO\n\n\n";
            }
        }
    }
    void makeGraph(int e, int v)
    {
        krawedzie = new edge *[e];
        wierholki = new vertex[v];
        V=v;
        E=e;
        for (int j = 0; j < v; j++)
            {
                wierholki[j].numer = j;
                // std::cout<<wierholki[j].numer<<j<<std::endl;
            }
    }

    // void dijxtra(int n)
    // {
    //     int tab[n-1];

    // }

    int getDirectDist(int n, int m)
    {
        //std::cout << "\n getDiresctdist ( " << n << ", " << m << ")";
        if (n == m)
            return 0;
        vertex *a = &wierholki[n];
        vertex *b = &wierholki[m];

        if (a->mojesomsiady == nullptr)
        {
            std::cout << "nie mo somsiadow";
            return 9999;
        }
        listaInc *pom = a->mojesomsiady;
        do
        {

            //          if (pom->krawedz->deuno==pom)
            // {
            //         if(pom->krawedz->dos==b)
            //         return pom->krawedz->weight;

            // }
            // else
            // {
            //            if(pom->krawedz->uno==b)
            //         return pom->krawedz->weight;
            // }
            //std::cout<<"przed ifem";
            if (pom->krawedz->uno == b || pom->krawedz->dos == b)
                return pom->krawedz->weight;
            //std::cout<<"poifie";
            pom = pom->next;
            //std::cout<<"\nobrot";
        } while (pom != nullptr);

        return 9999;
    }
}; //koniec grafu


void dijxtra(graph* graf, int pocz)
    {
        int temp=0;
        int v=graf->V;
        int * d=new int[v];
        int * p=new int[v];
        bool* isVisited=new bool [v];
        priorq * head=new priorq;
        priorq* tempq=nullptr;
        priorq * tempq2=nullptr;
       listaInc * tempq3=nullptr;
        for (int i=0;i<v;i++)
        {
           
                d[i]=9999;
                p[i]=i;
           
            //std::cout<<temp;
            //std::cout<<temp<<std::endl;
        }
        d[pocz]=0;
        for (int i=0;i<v;i++)
        {
            head->add(&(graf->wierholki[i]),d[i]);
        }
        //wyswietlKolejke(head);
        //std::cout<<" jestem" ;
        //getchar();
        while(head->next!=nullptr)
        {   
            tempq=head->pop();
            tempq3=tempq->myvertex->mojesomsiady;
           // std::cout<<"spopowalem "<<tempq->myvertex->numer<<" o wadze "<<tempq->weight<<std::endl;
        // wyswietlKolejke(head);
            while(tempq3!=nullptr)
            {  
                int waga= tempq3->krawedz->weight; 
                int nr;
                if(tempq3->krawedz->uno==tempq->myvertex)
                {
                    nr=tempq3->krawedz->dos->numer;
                }
                else
                {
                    nr=tempq3->krawedz->uno->numer;
                }
                
                if(isVisited[nr]!=1)
                {
                    if(waga+ tempq->weight < d[nr])
                    {
                        d[nr]=waga + tempq->weight;
                        p[nr]=tempq->myvertex->numer;
                       head->takelem(nr);
                       //std::cout<<" wzialem "<<tempq2->myvertex->numer<<" o wadze "<<tempq2->weight;
                        //tempq2->weight=d[nr];
                       // std::cout<<"pushuje "<<tempq2->myvertex->numer<<" o wadze "<<tempq2->weight<<std::endl;
                        head->add( &(graf->wierholki[nr]),d[nr]);
                    }
                }
                tempq3=tempq3->next;
            }
           isVisited[tempq->myvertex->numer]=1;
           delete tempq;
        }
        // for(int i=0;i<v;i++)
        // {
        //     std::cout<<d[i]<<" ";
        // }
        // std::cout<<std::endl;
        // for(int i=0;i<v;i++)
        // {
        //     std::cout<<p[i]<<" ";
        // }


        //wyswietlwynik(d,p,v,pocz);
        delete[] d;
        delete[] p;
        delete[] isVisited;
        delete head;
    }



} // namespace lista
lista::priorq *zrobliste(lista::graph *graf, int n)
{
    lista::priorq *zwrot = new lista::priorq;
    for (int i = 0; i < graf->getVnr(); i++)
    {
        //std::cout<<"elo";
        std::cout << graf->getDirectDist(n, i);
        zwrot->add(graf->getVertex(i), graf->getDirectDist(n, i));
        // std::cout<<"po razie";
    }
    return zwrot;
}
namespace matrix
{

class priorqm
{
public:
    priorqm *next = nullptr;
    int weight = 0;
    int mojnr=-1;

   
    void add(int newvertex, int dist)
    {
        priorqm *pom= this->next;
        priorqm *pomprev= this;
     

        priorqm *newpriorqm = new priorqm;
        newpriorqm->mojnr = newvertex;
        newpriorqm->weight = dist;

        while (pom != nullptr && pom->weight < dist)
        {
            pomprev = pom;
            pom = pom->next;
        }

        if (pom != nullptr && pom->weight >= dist)
            newpriorqm->next = pom;
        pomprev->next = newpriorqm; // niwc lub koniec
    }
    void push(priorqm* pushed)
    {
        priorqm *pom=this->next;
        priorqm *pomprev= this;
    

        while (pom != nullptr && pom->weight < pushed->weight)
        {
            pomprev = pom;
            pom = pom->next;
        }

        if (pom != nullptr && pom->weight >= pushed->weight)
            pushed->next=pom;
        pomprev->next=pushed;


    }
    priorqm *takelem(int n)
    {
        priorqm *pom= this->next;
        priorqm *pom2 = this;
        while(pom!=nullptr && pom->mojnr!=n)
        {
            pom = pom->next;
            pom2=pom2->next;
        }
    
       
        pom2->next = pom->next;
        return pom;
    }
    priorqm *pop()
    {
        priorqm *pom= this->next;
        this->next = this->next->next;

        return pom;
    }
    void wyswietl()
    {
        priorqm *pom = this->next;
        //pom=pom->next;
        std::cout << "wyswitlam\n";

        while (pom != nullptr)
        {
            std::cout << "nr: " << pom->mojnr << " dist: " << pom->weight << std::endl;
            pom = pom->next;
        }
    }
};

class graph
{
public:
    int **matrix;
    int V;
    int E;

    void makeGraph(int n)
    {
        V = n;
        matrix = new int *[V];
        for (int i = 0; i < V; i++)
        {
            matrix[i] = new int[V];
            for (int j = 0; j < V; j++)
            {
                matrix[i][j] = 0;
            }
        }
    }

    ~graph()
    {
        for (int i = 0; i < V; i++)
        {
            delete[] matrix[i];
        }
       
    }

    void addEdge(int x, int y, int w)
    {
        matrix[x][y] = w;
        matrix[y][x] = w;
    }

    int getDirectDist(int x, int y)
    {
        if(matrix[x][y]!=0)
        return matrix[x][y];
        else
        {
            return 9999;
        }
        
    }
    void readGraph(std::string nazwa)
    {
        std::ifstream plik(nazwa);
        int odczyt;
        int wpocz;
        int wkon;
        int waga;
        int i = 0;
        int wstartowy;
        if (plik.is_open() == true)
        {
            plik >> E >> V >> wstartowy;
            makeGraph(V);

            for (int j = 0; j < E; j++)
            {
                plik >> wpocz >> wkon >> waga;
                addEdge(wpocz, wkon, waga);

                // std::cout<<wierholki[j].numer<<j<<std::endl;
            }
            plik.close();
        }
    }

    void printGraph()
    {
        for (int i = 0; i < V; i++)
        {

            for (int j = 0; j < V; j++)
            {
                std::cout << matrix[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

}; //koniec grafu
void wyswietlKolejke(priorqm* head)
{
        priorqm* tempq;
        priorqm* tempq2;
        tempq=head;
        tempq=tempq->next;
        while(tempq!=nullptr)
        {
            std::cout<<" numer: "<<tempq->mojnr<<" o wadze"<<tempq->weight<<"\n";
            tempq=tempq->next;
        }
        std::cout<<"\n";

}
void dijxtra(graph* graf, int pocz)
{
        int temp=0;
        int v=graf->V;
        int * d=new int[v];
        int * p=new int[v];
        bool* isVisited=new bool [v];
        priorqm * head=new priorqm;
        priorqm* tempq=nullptr;
        priorqm * tempq2=nullptr;

        for (int i=0;i<v;i++)
        {
            if((temp=graf->getDirectDist(pocz,i))==0)
            {
                d[i]=9999;
                p[i]=-1;
            }else
            {
                d[i]=temp;
                 
                p[i]=pocz;
            }
            //std::cout<<temp;
            
        }
        d[pocz]=0;
        for (int i=0;i<v;i++)
        {
            head->add(i,d[i]);
        }
       // wyswietlKolejke(head);
        //std::cout<<" jestem" ;
        //getchar();
        while(head->next!=nullptr)
        {
            tempq=head->pop();
            //std::cout<<"spopowalem "<<tempq->mojnr<<" o wadze "<<tempq->weight<<std::endl;
        // wyswietlKolejke(head);
            for(int i=0;i<v;i++)
            {
                if(isVisited[i]!=1 && i!=tempq->mojnr)
                {
                    if(graf->getDirectDist(tempq->mojnr, i)+ tempq->weight < d[i])
                    {
                        d[i]=graf->getDirectDist(tempq->mojnr, i) + tempq->weight;
                        p[i]=tempq->mojnr;
                       tempq2=head->takelem(i);
                      // std::cout<<" wzialem "<<tempq2->mojnr<<" o wadze "<<tempq2->weight;
                        tempq2->weight=d[i];
                       // std::cout<<"pushuje "<<tempq2->mojnr<<" o wadze "<<tempq2->weight<<std::endl;
                        head->push(tempq2);
                    }
                }
            }
           isVisited[tempq->mojnr]=1;
           
        }
        // for(int i=0;i<v;i++)
        // {
        //     std::cout<<d[i]<<" ";
        // }
        // std::cout<<std::endl;
        // for(int i=0;i<v;i++)
        // {
        //     std::cout<<p[i]<<" ";
        // }
    //wyswietlwynik(d,p,v,pocz);
delete head;
delete [] isVisited;

}
} // namespace matrix
double testmatrix(double procent, int rozmiar)
{
   
    std::random_device rd;
    std::uniform_int_distribution<int> weight (1,99);
    std::uniform_int_distribution<int> edg (1,rozmiar-1);
    std::uniform_int_distribution<int> sto (0,100);
    double maxedges= rozmiar* (rozmiar-1)/2*procent/100;
    //std::cout<<"maxedges = "<<maxedges<<std::endl;
    int edgescounter=0;
    int a,b,c;
    double odpowiedzi[100];
    double odpowiedz=0;

    for(int w=0;w<100;w++)
    {
        edgescounter=0;
        matrix::graph G;
        G.makeGraph(rozmiar);

        for(int i=0; i< rozmiar-1 && edgescounter<=maxedges;i++)
        {
            G.addEdge(i,i+1,weight(rd));
            edgescounter++;
        }

            //int step=maxedges/(maxedges*procent/100-edgescounter);
            //int counter=0;

        for(int i=0; i < rozmiar && edgescounter<=maxedges ; i++)
        {
            for (int j=0; j<rozmiar && edgescounter<=maxedges ; j++)
            {
                c=sto(rd);
                if (i!=j && c<=procent && G.getDirectDist(i,j)==9999)
                {
                     G.addEdge(i,j,weight(rd));
                    edgescounter++;
                }
            }
        }
            //G.printGraph();
        auto begin= std::chrono::high_resolution_clock::now();
            dijxtra(&G,0);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end-begin;

        odpowiedzi[w]=elapsed.count();
    }
    for(int w=0;w<100;w++)
    {
        odpowiedz+=odpowiedzi[w];
    }
    odpowiedz=odpowiedz/100;
    return odpowiedz;
}

void testowaniematrix()
{
    int rozmiary[5]={10,50,100,500,1000};

    for(int j=25;j<=100;j=j+25)
    {
        for(int i=0; i<5; i++)
        {
            std::cout<<"dla wypelnienia "<<j<<"\% i "<<rozmiary[i]<<" krawedzi "<<testmatrix(j,rozmiary[i])<<std::endl;
        }
    }
}

double testlista(double procent, int rozmiar)
{
   
    std::random_device rd;
    std::uniform_int_distribution<int> weight (1,99);
    std::uniform_int_distribution<int> edg (1,rozmiar-1);
    std::uniform_int_distribution<int> sto (0,100);
    double maxedges= rozmiar* (rozmiar-1)/2*procent/100;
    int maxed=maxedges;
    //std::cout<<"maxedges = "<<maxedges<<std::endl;
    int edgescounter=0;
    int a,b,c;
    double odpowiedzi[100];
    double odpowiedz=0;

    for(int w=0;w<100;w++)
    {
        int macierz[rozmiar][rozmiar];
        for(int i=0;i<rozmiar;i++)
        {
            for(int j=0;j<rozmiar;j++)
            {
                macierz[i][j]=0;
            }
        }
        edgescounter=0;
        lista::graph G;
        G.makeGraph(maxed,rozmiar);
    for(int i=0;i<rozmiar-1;i++)
    {
        if(edgescounter<=maxed)
        {
            G.addEdge(edgescounter,i,i+1,weight(rd));
            edgescounter++;
            macierz[i][i+1]=1;
            macierz[i+1][i]=1;
        }
    }


        for(int i=0;i<rozmiar;i++)
        {
            for(int j=0;j<rozmiar;j++)
            {
                if(i!=j && edgescounter<maxed && sto(rd)<=procent && macierz[i][j]==0)
                {
                    G.addEdge(edgescounter,i,j,weight(rd));
                    edgescounter++;
                    macierz[i][j]=1;
                    macierz[j][i]=1;
                }
            }
        }
            //G.printGraph();
        auto begin= std::chrono::high_resolution_clock::now();
            dijxtra(&G,0);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end-begin;

        odpowiedzi[w]=elapsed.count();
    }
    for(int w=0;w<100;w++)
    {
        odpowiedz+=odpowiedzi[w];
    }
    odpowiedz=odpowiedz/100;
    return odpowiedz;
}

void testowanielista()
{
    int rozmiary[5]={10,50,100,500,1000};

    for(int j=25;j<=100;j=j+25)
    {
        for(int i=0; i<5; i++)
        {
            //std::cout<<"jurde ni"<<std::endl;
            std::cout<<"dla wypelnienia "<<j<<"\% i "<<rozmiary[i]<<" krawedzi "<<testlista(j,rozmiary[i])<<std::endl;
        }
    }
}


int main()
{
    // lista::priorq* odp;
    // lista::graph graf;
    // graf.readGraph("dane1.txt");
    //  graf.somsiady(2);
    //  std::cout<<std::endl<<graf.getDirectDist(2,0)<<"  "<<graf.getDirectDist(2,1)<<"  "<<graf.getDirectDist(2,3)<<std::endl;
    //    getchar();
    //  lista::priorq* kolejka=zrobliste(&graf,2);
    //    getchar();
    //      kolejka->wyswietl();
    //      odp=kolejka->takefirstelem();
    //      kolejka->wyswietl();
    //      std::cout<<odp->weight<<odp->myvertex->numer;
    //      odp=kolejka->takefirstelem();
    //      kolejka->wyswietl();
    //      std::cout<<odp->weight<<odp->myvertex->numer;
    //      odp=kolejka->takefirstelem();
    //      kolejka->wyswietl();
    //      std::cout<<odp->weight<<odp->myvertex->numer;

std::cout<<"\nLISTA\n";
//dijxtra(&graf, 0);
//std::cout<<testlista(25,100);
// testowanielista();
std::cout<<"\nMACIERZ\n";
//     matrix::graph grafik;
//     grafik.readGraph("dane1.txt");
//     grafik.printGraph();
//     dijxtra(&grafik, 0);
    testowaniematrix();
}