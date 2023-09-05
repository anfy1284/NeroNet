
template<typename T>
class QueueNode;

template<typename T>
class Queue{ 
 
    public:
    Queue();
    ~Queue();
    int size();
    int count;
    QueueNode<T> *addAtLast(T v);
    QueueNode<T> *addAtFirst(T v);
    T *get(int index);
    QueueNode<T> *getFirstNode();
    
    class Selection{
        
        public:
        Selection(Queue<T> *vOwner);
        void reset();
        bool next();
        bool eof();
        T get();
        
        private:
        Queue<T> *owner;
        QueueNode<T> *currentNode;
    };

    Selection *select(){
        Selection *newSelection = new Selection(this);
        return newSelection;
    };

    private:
    QueueNode<T> *firstNode;
    QueueNode<T> *lastNode;
    QueueNode<T> *addFirstNode(T v);

};

template<typename T>
class QueueNode{

    public:
    QueueNode(Queue<T> *vOwner);
    QueueNode(Queue<T> *vOwner, bool isFirstNode);
    T getValue();
    void setValue(T v);
    QueueNode *insertNext(T v);
    QueueNode *insertPrev(T v);
    void del();
    bool isBegin;
    bool isEnd;
    QueueNode *nextNode;
    // TODO: remove to private


    private:
    void refreshIndexes();
    QueueNode *prevNode;
    int index;
    T value;
    Queue<T> *owner;

};


//EXCEPTIONS
class QueueIsEmptyException{};
class QueueIsNotEmptyException{};
//EXCEPTIONS//

////////
//Queue
////////

template<typename T>
Queue<T>::Queue()
{
    this->count = 0;
    this->firstNode = NULL;
    this->lastNode = NULL;
}

template<typename T>
Queue<T>::~Queue()
{
}

template<typename T>
int Queue<T>::size()
{
    return count;
}

template<typename T>
inline QueueNode<T> *Queue<T>::addFirstNode(T v)
{
    // if(this->count != 0){
    //     throw QueueIsNotEmptyException;
    // }
    firstNode = new QueueNode(this, true);
    lastNode = firstNode;
    firstNode->setValue(v);
    count = 1;
    return firstNode;
}

template<typename T>
QueueNode<T> *Queue<T>::addAtLast(T v){
    if(count == 0)
        return addFirstNode(v);
    else{
        count++;
        QueueNode<T> *newNode = this->lastNode->insertNext(v);
        this->lastNode = newNode;
        return newNode;
    }
}

template<typename T>
QueueNode<T> *Queue<T>::addAtFirst(T v){
    if(count == 0)
        return addFirstNode(v);
    else{
        count++;
        QueueNode<T> *newNode = this->firstNode->insertPrev(v);
        this->firstNode = newNode;
        return newNode;
    }
}

template<typename T>
inline T *Queue<T>::get(int index)
{
    //return QueueValue();
    return NULL;
}

template<typename T>
inline QueueNode<T> *Queue<T>::getFirstNode()
{
    return this->firstNode;
}

////////
//Queue/
////////

////////
//QueueNode
////////

template<typename T>
inline QueueNode<T>::QueueNode(Queue<T> *vOwner)
{
    // this->QueueNode(vOwner, false);
    
    // TODO: Убрать дублирующийся код!
    bool isFirstNode = false;

    this->index = 0;
    this->owner = vOwner;
    if(isFirstNode){
        this->isBegin = true;
        this->isEnd = true;
    }else{
        this->isBegin = false;
        this->isEnd = false;
    }

}

template<typename T>
inline QueueNode<T>::QueueNode(Queue<T> *vOwner, bool isFirstNode)
{
    this->index = 0;
    this->owner = vOwner;
    if(isFirstNode){
        this->isBegin = true;
        this->isEnd = true;
    }else{
        this->isBegin = false;
        this->isEnd = false;
    }
}

template<typename T>
T QueueNode<T>::getValue()
{
    return value;
}

template<typename T>
void QueueNode<T>::setValue(T v){
    value = v;
}

template<typename T>
inline QueueNode<T> *QueueNode<T>::insertNext(T v)
{
    QueueNode *newNode = new QueueNode(this->owner);
    
    newNode->setValue(v);
    newNode->prevNode = this;

    if(this->isEnd){
        newNode->isEnd = true;
        this->isEnd = false;
    }
    else{
        nextNode = this->nextNode;
        nextNode->prevNode = newNode;
        newNode->nextNode = nextNode;
    }

    this->isEnd = false;
    this->nextNode = newNode;
    newNode->index = this->index + 1;

    newNode->refreshIndexes();

    return newNode;
}

template<typename T>
inline QueueNode<T> *QueueNode<T>::insertPrev(T v)
{
    QueueNode *newNode = new QueueNode(this->owner);
    
    newNode->setValue(v);
    newNode->nextNode = this;

    if(this->isBegin){
        newNode->isBegin = true;
        this->isBegin = false;
    }
    else{
        prevNode = this->prevNode;
        prevNode->nextNode = newNode;
        newNode->prevNode = prevNode;
    }

    this->isBegin = false;
    this->prevNode = newNode;
    newNode->index = this->index;

    newNode->refreshIndexes();

    return newNode;
}

template<typename T>
inline void QueueNode<T>::del()
{
    int size = this->owner->size();
    
    if(size == 0){
        //throw QueueIsEmptyException;
    }else if(size == 1){
        this->owner->count = 0;
    }else{
        if(this->isBegin){

        }
    }
    

}

template<typename T>
inline void QueueNode<T>::refreshIndexes()
{   
    QueueNode *cNode = this;
    int i = this->index;
    while(!cNode->isEnd){
        cNode->index = i;
        cNode = cNode->nextNode;
        i++;
    }
}

////////
//QueueNode/
////////

template <typename T>
inline bool Queue<T>::Selection::next()
{
    if(this->currentNode == NULL){
        
        this->currentNode = this->owner->getFirstNode();
        
        if(this->currentNode == NULL){
            return false;
        }

        return true;
    }

    if(this->currentNode->isEnd)
        return false;

    this->currentNode = this->currentNode->nextNode;
    return true;
}

template <typename T>
inline bool Queue<T>::Selection::eof()
{
    if(this->currentNode == NULL)
        return true;
    if(this->currentNode->isEnd)
        return true;

    return false;
}

template <typename T>
inline T Queue<T>::Selection::get()
{
    return currentNode->getValue();
}

template <typename T>
inline void Queue<T>::Selection::reset()
{
    this->currentNode = NULL;
}

template <typename T>
inline Queue<T>::Selection::Selection(Queue<T> *vOwner)
{
    this->owner = vOwner;
    this->reset();
}
