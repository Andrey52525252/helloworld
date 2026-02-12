bool init (subforwardlist **sfl) {
    if (sfl == nullptr) {
        return false;
    }
    *sfl = nullptr;
    return true;
}

bool push_back(subforwardlist **sfl, int d) {
    if (sfl == nullptr) {
        return false;
    }
    subforwardlist* new_node = new subforwardlist();
    new_node -> data = d;
    new_node -> next = nullptr;

    if (*sfl == nullptr) {
        *sfl = new_node;
        return true;
    }
    subforwardlist* current = *sfl;
    while (current -> next != nullptr) {
        current = current -> next;
    }
    current -> next = new_node;
    return true;
}

int pop_back(subforwardlist **sfl) {
    if (sfl == nullptr || *sfl == nullptr) {
        return 0;
    }
    subforwardlist* current = *sfl;
    if (current -> next == nullptr) {
        int r = current -> data;
        delete current;
        *sfl = nullptr;
        return r;
    }

    while (current -> next -> next != nullptr) {
        current = current -> next;
    }
    int r = current -> next -> data;
    delete current -> next;
    current -> next = nullptr;
    return r;
}

bool push_forward(subforwardlist **sfl, int d) {
    subforwardlist* new_node = new subforwardlist();
    new_node -> data = d;
    new_node -> next = *sfl;
    *sfl = new_node;
    return true;
}

int pop_forward(subforwardlist **sfl) {
    if (sfl == nullptr || *sfl == nullptr) {
        return 0;
    }
    subforwardlist *first_node = *sfl;
    int d = first_node -> data;
    *sfl = first_node -> next;
    delete first_node;
    return d;
}

bool push_where(subforwardlist **sfl, unsigned int where, int d) {
    if (sfl == nullptr) {
        return false;
    }
    if (where == 0) {
        return push_forward(sfl, d);
    }

    subforwardlist* new_node = new subforwardlist();
    new_node -> data = d;
    new_node -> next = nullptr;
    subforwardlist* current = *sfl;

    if (*sfl == nullptr) {
        if (where == 0) {
            *sfl = new_node;
            return true;
        }
        else {
            delete new_node;
            return false;
        }
    }

    unsigned int count = 0;
    while (current -> next != nullptr && count < where-1) {
        current = current -> next;
        count ++;
    }

    if (count != where - 1) {
        delete new_node;
        return false;
    }
    new_node -> next = current -> next;
    current -> next = new_node;
    return true;
}

int erase_where(subforwardlist **sfl, unsigned int where) {
    if (*sfl == nullptr) {
        return 0;
    }
    if (where == 0) {
        return(pop_forward(sfl));
    }

    subforwardlist* current = *sfl;
    unsigned int count = 0;
    while (current -> next != nullptr && count < where-1) {
        current = current -> next;
        count ++;
    }

    if (count != where-1) {
        return 0;
    }
    int r = current -> next -> data;
    subforwardlist* to_delete = current -> next;
    current -> next = current -> next -> next;
    delete to_delete;

    return r;
}

void clear (subforwardlist **sfl) {
    while (*sfl != nullptr) {
        pop_forward(sfl);
    }
}

unsigned int size (subforwardlist *sfl) {
    if (sfl == nullptr) return 0;
    unsigned int count = 0;
    while (sfl != nullptr) {
        sfl = sfl -> next;
        count ++;
    }
    return count;
}