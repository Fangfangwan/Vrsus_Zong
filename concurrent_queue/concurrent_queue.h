#include <pthread.h>
#include <cstdlib>
#include <cstdio>

template <class T>
    class ConcurrentQueue {

    typedef struct Node {
        T data;
        Node* next;
    } Node;

    public:
        
        ConcurrentQueue(): head(NULL), tail(NULL) {
            pthread_mutex_init(&lock, 0);
        }
  
        ~ConcurrentQueue() { this->clear() }

        ConcurrentQueue<T>& operator= (const ConcurrentQueue<T>& rhs);
        
        bool push( const T& data );           // can fail when run out of RAM
        bool pop( T& data );                  // return false when queue is empty
        void clear();

    private:

        Node* head;
        Node* tail;
        mutable pthread_mutex_t lock;

};

/*
template <class T>
ConcurrentQueue<T>& ConcurrentQueue<T>::operator=
    (const ConcurrentQueue<T>& rhs) {

    if(this != &rhs) { // self-assignment check

        
        pthread_mutex_lock( &(this->lock) );
        this->clear(); // TODO deadlock
      
        pthread_mutex_lock( &(rhs.lock) );

        if (!rhs.head) { // rhs empty - do nothing

        } else if ( rhs.head == rhs.tail ) { // rhs has only 1 element
            
            Node *n = (Node*) malloc(sizeof(Node));
            if (!n) 
        

        pthread_mutex_unlock( &(rhs.lock) );
        pthread_mutex_unlock( &(this->lock) );

    }
    
    return *this;

};*/

template <class T> bool ConcurrentQueue<T>::push( const T& data ) {

    Node *n = (Node*)malloc( sizeof(Node) );
    if(!n) return false;
    
    n->data = data;
    n->next = NULL;
    
    pthread_mutex_lock(&lock);
    // the queue is empty
    if ( !tail ) head = tail = n;
    else {
        tail->next = n;
        tail = n;
    }
    
    pthread_mutex_unlock(&lock);

    return true;
}

template <class T> bool ConcurrentQueue<T>::pop( T& data ) {

    pthread_mutex_lock(&lock);
    if (!head) {
        
        pthread_mutex_unlock(&lock);
        return false;

    // has only 1 element
    } else if (head == tail) {
        
        Node* tmp = head;
        head = tail = NULL;
        pthread_mutex_unlock(&lock);

        data = tmp->data;
        free(tmp);
        
        return true;

    } else {
        
        Node* tmp = head;
        head = tmp->next;
        pthread_mutex_unlock(&lock);

        data = tmp->data;
        free(tmp);
        return true;
        
    }
}

template <class T> void ConcurrentQueue<T>::clear() {

    pthread_mutex_lock(&lock);
    
    if(!head) {  // do nothing
        
    } else if (head == tail) {

        free(head);
        head = tail = NULL;

    } else {
        
        Node* tmp = head->next;
        while(!tmp) {
            free(head);
            head = tmp;
            tmp = head->next;
        }
        free(head);
        head = tail = NULL;
        
    }
    
    pthread_mutex_unlock(&lock);

}
