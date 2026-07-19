#include<iostream>
#include<stdio.h>

using namespace std;

struct edge;

struct vertex
{
    char data;
    vertex*vnext;
    edge*edgelist;
    bool visited;
    
};

struct edge
{
    int weight;
    edge*enext;
    
    vertex*v;

};
vertex*graph=NULL;




struct queue
{
    vertex*data;
    queue*next;
}; 

queue*front=NULL;
queue*rear= NULL;


void Enqueue(vertex* value)
{
    queue*temp;
    temp=(queue*)malloc(sizeof(queue));
    temp->data=value;
    temp->next=nullptr;

    {
        front=temp;
        rear=temp;

        cout<<"\nThe value successfully queued\n";
        
    }
    
    else
    {

        
        cout<<"\nThe value successfully queued\n";


    }


}





vertex* Dequeue()
{
    queue*curr=front;
   
    
    {
        cout<<"List is empty, deletion not possible"<<endl;
        return;
    }

    {
        vertex* tmp = curr->data;
        free (curr);
        cout<<"\nValue Dequeued\n";
        rear=NULL;
        front=NULL;
        return tmp;
    }


    {
        front=front->next;

        free(curr);
        cout<<"\nValue Dequeued\n";
        return 0;
    }
    

}






void AddVertex (char value)
{
    temp=(vertex*)malloc(sizeof(vertex));
    temp->data=value; 
    temp->visited=false;
    

    if (graph==NULL)
    {
        graph=temp;
    }
    else
    {
        vertex*curr=graph;
        while(curr->vnext!=NULL)
        {
            curr=curr->vnext;
        }
        curr->vnext=temp;
    }


}

void removeAllOcc(char value)
{
    vertex*curr=graph;

        while (curr!=NULL)
        {
            edge*ecurr=curr->edgelist;
            edge*prev1;
            while(ecurr!=NULL)
            {
                if (value==curr->edgelist->v->data)
                {
                    curr->edgelist=curr->edgelist->enext;
                    free(ecurr);
                    break;
                }
                prev1=curr->edgelist;
                ecurr=ecurr->enext;
                while(ecurr!=NULL)
                {
                    if (value==ecurr->v->data)
                    {
                        prev1->enext=ecurr->enext;
                        free(ecurr);
                        break;

    
                    }
                    prev1=ecurr;
                    ecurr=ecurr->enext;
                }
                
                ecurr=ecurr->enext;
            }
            curr=curr->vnext;
        }
    return;

}


void RemoveVertex(char value)
{
    vertex*curr=graph;
    vertex* prev;

    while (curr!=NULL)
    {
        if (value==curr->data)
        {
            graph=graph->vnext;
            edge*ecurr=curr->edgelist;

            while(ecurr!=NULL)
            {
                curr->edgelist=curr->edgelist->enext;
                free(ecurr);
                ecurr=curr->edgelist;
                
            }
            free(curr);
            return;
        }

        prev=graph;
        curr=curr->vnext;

        while (curr !=NULL)
        {
            if (value==curr->data)
            {
                prev->vnext=curr->vnext;
                edge* ecurr = curr->edgelist;

                while(ecurr!=NULL) 
                {
                    curr->edgelist=curr->edgelist->enext;  

                    free(ecurr);  

                    ecurr= curr->edgelist;  
                    
                }
                free(curr); 
                
            }
            prev=curr;
            curr=curr->vnext;
        }

        removeAllOcc(value);

    }
    
}

vertex* GiveAddress(char a)
{
    vertex*curr=graph;
    vertex*address;

    while (curr!=NULL)
    {
        if (a==curr->data)
        {
            return curr;
        }
      curr=curr->vnext;
    }

    cout<<"The vertex doesnot exists"<<endl;
    return 0;
    
}


void AddEdge(char vert1,char vert2)
{
    vertex*curr=graph;
    vertex*curr2=graph;
    
    edge*ecurr1;
    edge*ecurr2;

    while(curr!=NULL)
    {
        if (vert2==curr->data)
        {
            vertex*address1=GiveAddress(vert2);

            while (curr2!=NULL)
            {
                if (vert1==curr2->data)
                {
                    
                    edge*temp;
                    temp=(edge*)malloc(sizeof(edge));
                    temp->v=address1;
                    temp->enext=NULL;
                    temp->weight=0;
                    
                   
                    if (curr2->edgelist==NULL)
                    {
                        curr2->edgelist=temp;
                    }
                    else
                    {
                        ecurr1=curr2->edgelist;
                        while(ecurr1->enext!=NULL)
                        {
                            ecurr1=ecurr1->enext;
                        }
                        ecurr1->enext=temp;

                    }
                }
                curr2=curr2->vnext;
                
            }

            vertex*address2=GiveAddress(vert1);

            edge*temp2;
            temp2=(edge*)malloc(sizeof(edge));
            temp2->v=address2;
            temp2->enext=NULL;
            temp2->weight=0;

            if (curr->edgelist==NULL)
            {
                curr->edgelist=temp2;
            }
            else
            {
                ecurr2=curr->edgelist;
                while(ecurr2->enext!=NULL)
                {
                    ecurr2=ecurr2->enext;
                }
                ecurr2->enext=temp2;

            }

        }
        curr=curr->vnext;
    }
}





void display()
{
    vertex*curr=graph;
    edge*ecurr;
    if (graph!=NULL)
    {
        while(curr!=NULL)
        {
            
            cout<<curr->data<<" | ";
            ecurr=curr->edgelist;
            while(ecurr!=NULL)
            {
                cout<<ecurr->v->data<<" ";
                ecurr=ecurr->enext;

            }
            curr=curr->vnext;


            cout<<endl;
        }
    }
    else
    {
        cout<<"Graph is empty"<<endl;
    }
}


void degree( int value)
{
    int count=0;
    vertex* curr=graph;
    if (value==curr->data)
    {
        edge*ecurr=curr->edgelist;
        while(ecurr!=NULL)
        {
            count++;
            ecurr=ecurr->enext;
        }

        cout<<count;

    }
}


void BFS() 
{
    vertex* curr = graph;
    vertex*output;
    Enqueue(curr);

    edge* ecurr=curr->edgelist;
    while(front!=NULL)
    {
        Dequeue();

    }


}    





        
    



    
        
        


    







int main ()
{
    int choice; 
    char val,num1,num2;
        
        while (true)
        {
            cout << "\n--- MENU ---\n";
            cout << "1. Add Vertex \n2. Display \n3. Add Edge \n4. Remove Vertex \n5. Matrix form  \n6. degree  \n";
            cout << "Enter choice: ";
            cin >> choice; 
            
            switch(choice) 
            {
                case 1:
                    cout << "Enter value to insert: ";
                    cin >> val;
                    AddVertex(val);
                    break;

                case 2:
                    display();
                    break;

                case 3:
                    cout << "Enter vertex 1:";
                    cin >> num1;
                    cout << "Enter vertex 2 to attach:";
                    cin >> num2;

                    AddEdge(num1,num2);
                    break;

                case 4:
                    cout << "Enter value to delete: ";
                    cin >> val;
                    RemoveVertex(val);
                    break;


                case 5:
                    cout << "Enter value to insert: ";
                    cin >> val;
                    degree(val);
                    break;

                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        }

    return 0;
}