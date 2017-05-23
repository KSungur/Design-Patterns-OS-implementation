
/**
 * SE 311 Project
 *
 * Kutayberk Sungur 20130601036
 *
 * Ataberk Uzkal 20130601046
 *
 * Source file Pattern Flow
 * Observer Pattern
 * Composite Pattern
 * Iterator Pattern
 * Command Pattern
 * Abstract Factory Pattern
 * Singleton Pattern
 *
 */

#include <iostream>
#include <vector>
#include <string>


using namespace std;

class Computer;

/**
 * Semi observer
 */
class Components {
public:
    virtual void deviceReset() = 0;

/**
 * Notify Method Declaration
 */
    void Notify();

protected:
    Computer *myComputer;
};

/**
 * Notify Method Definition
 */
void Components::Notify() {

}

class CPU : public Components {
    ~CPU() {
        cout << "Terminate unfinished CPU tasks" << endl;
    }

public:
    CPU(Computer *comp) {
        myComputer = comp;
        cout << "CPU is loading..." << endl;
    }

    void deviceReset() {
        delete this;
    }
};

class Mouse : public Components {
    ~Mouse() {
        cout << "Disconnecting mouse" << endl;
    }

public:
    Mouse(Computer *comp) {
        myComputer = comp;
        cout << "Mouse is connected" << endl;
    }

    void deviceReset() {
        delete this;
    }

};

class Keyboard : public Components {
    ~Keyboard() {
        cout << "Disconnecting keyboard" << endl;
    }

public:
    Keyboard(Computer *comp) {
        myComputer = comp;
        cout << "Keyboard is connected" << endl;
    }

    void deviceReset() {
        delete this;
    }

};

class HDD : public Components {
    ~HDD() {
        cout << "Computer received shutdown command\n"
                "Initiating output stream to save changes" << endl;
    }

public:
    HDD(Computer *comp) {
        myComputer = comp;
        cout << "Hard Disk is loading..." << endl;
    }

    void deviceReset() {
        delete this;
    }
};


/**
 * Composite Component
 */
class Directory {
public:
    virtual ~Directory() {};

    virtual void Display(int indent) {};

    string getName() { return name; };

    virtual int getCount() { return 0; };

    virtual Directory *get(int) { return NULL; };

    virtual void Delete() {};
protected:
    Directory(string name) : name(name) {};
private:
    string name;
};

/**
 *  Abstract Iterator
 */
class AbstractIterator {
public:
    virtual void First() = 0;

    virtual void Next() = 0;

    virtual bool IsDone() const = 0;

    virtual Directory *CurrentItem() const = 0;

protected:
    AbstractIterator() {};
};

/**
 * Concrete Iterator
 *
 */
class CompositeIterator : public AbstractIterator {
public:
    CompositeIterator(Directory *composite) :
            _composite(composite), _current(0) {
    }

    void First() { _current = 0; };

    void Next() { _current++; };

    Directory *CurrentItem() const {
        return (IsDone() ? NULL : _composite->get(_current));
    };

    bool IsDone() const {
        return _current >= _composite->getCount();
    };
private:
    Directory *_composite;
    int _current;
};

/**
 * Composite Pattern Leaf
 *
 */

class File : public Directory {
public:
    File(string name) : Directory(name) {};

    void Display(int indent) {
        for (int i = 1; i <= indent; i++) { cout << "-"; }
        cout << " " << getName() << endl;
    }
};

/**
 * Composite Pattern Composite
 */
class Node : public Directory {

public:
    Node(string name) : Directory(name) { cout << name << " Created\n"; };

    Directory *get(int index) { return elements[index]; };

    int getCount() { return elements.size(); };

    void Add(Directory *d) {
        elements.push_back(d);
        cout << d->getName() << " Added\n";
    };

    void Delete() {
        Directory *temp;
        CompositeIterator *i = CreateIterator();
        for (i->First(); !i->IsDone(); i->Next()) {
            i->CurrentItem()->Delete();
            cout << "Deleting " << i->CurrentItem()->getName() << endl;
            delete i->CurrentItem();
        }
        delete i;
    }

    void Remove(Directory *d) {
        CompositeIterator *i = CreateIterator();
        int count = 0;
        for (i->First(); !i->IsDone(); i->Next()) {
            if (i->CurrentItem()->getName() == d->getName()) {
                elements.erase(elements.begin() + count);
                delete i;
                return;
            } else count++;
        }
        delete i;
    }

    void Display(int indent) {
        for (int i = 1; i <= indent; i++) { cout << "-"; }
        cout << "+ " + getName() << endl;

        CompositeIterator *i = CreateIterator();
        for (i->First(); !i->IsDone(); i->Next())
            i->CurrentItem()->Display(indent + 2);
        delete i;
    }

    CompositeIterator *CreateIterator() {
        return new CompositeIterator(this);
    }

private:
    vector<Directory *> elements;
};

/**
* Command Pattern
* Command
*/
class OperatingSys {
public:
    virtual void exec() = 0;

protected:
    OperatingSys() {};
};

/**
* Commands
*/

class OpenFile : public OperatingSys {
public:
    OpenFile(OperatingSys *osFactory) {
        fileSystem = osFactory;
    }

    void exec() {
        fileSystem->exec();
    }

private:
    OperatingSys *fileSystem;
};

class WriteFile : public OperatingSys {
public:
    WriteFile(OperatingSys *osFactory) {
        fileSystem = osFactory;
    }

    void exec() {
        fileSystem->exec();
    }

private:
    OperatingSys *fileSystem;
};

class CloseFile : public OperatingSys {
public:

    CloseFile(OperatingSys *osFactory) {
        fileSystem = osFactory;
    }

    void exec() {
        fileSystem->exec();
    }

private:
    OperatingSys *fileSystem;
};

class ShutDownDevices : public OperatingSys {
    vector<Components *> components;
public:
    ShutDownDevices(vector<Components *> d) {
        components = d;
    }

    void exec() {
        for (unsigned long i = 0; i <= components.size() - 1; i++) {
            components[i]->deviceReset();
        }
    }
};

/**
* Invoker
*/

class FileInvoker {
public:
    OperatingSys *operatingSys;

    FileInvoker(OperatingSys *os) {
        operatingSys = os;
    }

    void exec() {
        operatingSys->exec();
    }
};

class FileSystem {
public:
    virtual void bootOS() = 0;

    virtual void loadFS() = 0;

};

/**
* Concrete Product 1
*/

class Linux : public FileSystem {
public:
    void bootOS() {
        cout << "Booting into Linux \n";
    }

    void loadFS() {
        Node *root = new Node("Linux Node");
        root->Add(new File("Linux Leaf"));
        Directory *_directory = new File("Linux Directory");
        root->Add(_directory);
        root->Display(1);

        cout << "\n---Initializing Kernel \n"
                "---Executing systemd \n"
                "user@user:~$";
    }
};

/**
* Concrete Product 2
*/

class BSD : public FileSystem {
public:
    void bootOS() {
        cout << "Booting into BSD \n";
    }

    void loadFS() {
        Node *root = new Node("BSD Node");
        root->Add(new File("BSD Leaf"));
        Directory *_directory = new File("BSD Directory");
        root->Add(_directory);
        root->Display(1);

        cout << " \n---Initializing Kernel \n"
                "---Executing systemd \n"
                "user@user:~#";
    }

};

/**
* Concrete Product 3
*/

class NT : public FileSystem {
public:
    void bootOS() {
        cout << "Booting into NT \n";
    }

    void loadFS() {
        Node *root = new Node("Windows NT Node");
        root->Add(new File("Windows NT Leaf"));
        Directory *_directory = new File("Windows NT Directory");
        root->Add(_directory);
        root->Display(1);

        cout << "\n---DO NOT use Windows, use GNU/Linux or BSD instead\n"
                "---Initializing Windows Kernel \n"
                "Microsoft Windows [Version 10.0.14393] \n"
                "(c) 2016 Microsoft Corporation. All rights reserved. \n"
                "C:\\Users\\User> \n";
    }


};

/**
* Abstract factory
*
*/

class OSFactory {
public:
    virtual FileSystem *loadFileSystem() = 0;

    OSFactory() {}

    virtual FileSystem *boot() = 0;

    virtual OpenFile *openFile() = 0;

    virtual WriteFile *writeFile() = 0;

    virtual CloseFile *closeFile() = 0;


};

/**
* Each concrete factory corresponds to one product
* family. It creates all possible products of
* one kind.
*/
class LinuxFactory : public OSFactory {
public:
    FileSystem *loadFileSystem() {
        return new Linux;
    }

    FileSystem *boot() {
        return new Linux;
    }

    OpenFile *openFile() {
        cout << "\nBoot Successful \n"
                "Opening file in Linux OS\n"
                "--/Awaiting input stream..." << endl;
        return NULL;
    }

    WriteFile *writeFile() {
        cout << "Write file in Linux OS" << endl;
        return NULL;
    }

    CloseFile *closeFile() {
        cout << "Closing file in Linux OS" << endl;
        return NULL;
    }

    FileSystem *getName() {
        return new Linux;
    }

};

/**
* Concrete factory creates concrete products, but
* returns them as abstract.
*/
class BSDFactory : public OSFactory {
public:
    FileSystem *loadFileSystem() {
        return new BSD;
    }

    FileSystem *boot() {
        return new BSD;
    }

    OpenFile *openFile() {
        cout << "\nBoot Successful \n"
                "Opening file in BSD OS\n"
                "--/Awaiting input stream..." << endl;
        return NULL;
    }

    WriteFile *writeFile() {
        cout << "Write file in BSD OS" << endl;
        return NULL;
    }

    CloseFile *closeFile() {
        cout << "Closing file in BSD OS" << endl;
        return NULL;
    }

};

class NTFactory : public OSFactory {
public:
    FileSystem *loadFileSystem() {
        return new NT;
    }

    FileSystem *boot() {
        return new NT;
    }

    OpenFile *openFile() {
        cout << "\nBoot Successful \n"
                "Opening file in Windows OS\n"
                "--/Awaiting input stream..." << endl;
        return NULL;
    }

    WriteFile *writeFile() {
        cout << "Write file in Windows OS" << endl;
        return NULL;
    }

    CloseFile *closeFile() {
        cout << "Closing file in Windows OS" << endl;
        return NULL;
    }
};

/**
* Abstract Factory Client
*
*/

class OSClient {
private:
    OSFactory *factory;

public:
    OSClient(OSFactory *f) {
        factory = f;
    }

    void display_IO() {
        FileSystem *fileSystem[] = {
                factory->boot(),
                factory->loadFileSystem(),
        };
        fileSystem[0]->bootOS();
        fileSystem[1]->loadFS();
        factory->openFile();
        factory->writeFile();
        factory->closeFile();
    }

};


/**
 * Singleton Pattern
 */

class Computer {
private:
    vector<Components *> components;
    OSFactory *osFactory;
    OperatingSys *operatingSys;
    char osType;
public:
    Computer() {
        components.push_back(new HDD(this));
        components.push_back(new CPU(this));
        components.push_back(new Keyboard(this));
        components.push_back(new Mouse(this));

        cout << "GRUB MENU: \n"
                "Choose OS: \n "
                "l for Linux \n"
                "b for BSD \n"
                "n for WindowsNT" << endl;
        cin >> osType;

        switch (osType) {
            case 'l':
                osFactory = new LinuxFactory;
                break;
            case 'b':
                osFactory = new BSDFactory;
                break;
            case 'n':
                osFactory = new NTFactory;
                break;
            default:
                cout << "You did not choose a correct operating system.";
        }
        OSClient *c = new OSClient(osFactory);
        c->display_IO();
        delete c;
        operatingSys = new ShutDownDevices(components);
        operatingSys->exec();
    }

    ~Computer() {};
};


int main() {
    Computer *computer = new Computer();
    delete computer;
    return 0;
}

