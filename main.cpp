#include <iostream>
#include<vector>
#include <typeinfo>
#include <string>

using namespace std;

class FileSystem {
public:
    virtual void bootOS() = 0;

    virtual void loadFS() = 0;

//    virtual void openFile() = 0;
//
//    virtual void writeFile() = 0;
//
//    virtual void closeFile() = 0;

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
        cout << "---Initializing Kernel \n"
                "---Executing systemd \n"
                "user@user:~$";
    }

//    void openFile() {
//        cout << "Opening file in Linux OS" << endl;
//    }
//
//    void writeFile() {
//        cout << "Writing file in Linux OS" << endl;
//    }
//
//    void closeFile() {
//        cout << "Closing file in Linux OS" << endl;
//    }

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
        cout << "---Initializing Kernel \n"
                "---Executing systemd \n"
                "user@user:~#";
    }
//    void openFile() {
//        cout << "Opening file in BSD OS" << endl;
//    }
//
//    void writeFile() {
//        cout << "Writing file in BSD OS" << endl;
//    }
//
//    void closeFile() {
//        cout << "Closing file in BSD OS" << endl;
//    }

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
        cout << "---DO NOT use Windows, use GNU/Linux or BSD instead\n"
                "---Initializing Windows Kernel \n"
                "Microsoft Windows [Version 10.0.14393] \n"
                "(c) 2016 Microsoft Corporation. All rights reserved. \n"
                "C:\\Users\\User> \n";
    }
//
//    void openFile() {
//        cout << "Opening file in BSD OS" << endl;
//    }
//
//    void writeFile() {
//        cout << "Writing file in BSD OS" << endl;
//    }
//
//    void closeFile() {
//        cout << "Closing file in BSD OS" << endl;
//    }


};

/**
 * Abstract factory
 *
 */

class OSFactory {
public:
    virtual FileSystem *loadFileSystem()=0;

    virtual FileSystem *boot()=0;

    virtual FileSystem *openFile() = 0;

    virtual FileSystem *writeFile() = 0;

    virtual FileSystem *closeFile() = 0;
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

    FileSystem *openFile() {
        cout << "Opening file in Linux OS" << endl;
    }

    FileSystem *writeFile() {
        cout << "Writing file in Linux OS" << endl;
    }

    FileSystem *closeFile() {
        cout << "Closing file in Linux OS" << endl;
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

    FileSystem *openFile() {
        cout << "Opening file in BSD OS" << endl;
    }

    FileSystem *writeFile() {
        cout << "Writing file in BSD OS" << endl;
    }

    FileSystem *closeFile() {
        cout << "Closing file in BSD OS" << endl;
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

    FileSystem *openFile() {
        cout << "Opening file in Windows OS" << endl;
    }

    FileSystem *writeFile() {
        cout << "Writing file in Windows OS" << endl;
    }

    FileSystem *closeFile() {
        cout << "Closing file in Windows OS" << endl;
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
                factory->openFile(),
                factory->writeFile(),
                factory->closeFile(),
        };
        fileSystem[0]->bootOS();
        fileSystem[1]->loadFS();
//        fileSystem[2]->openFile();
//        fileSystem[3]->writeFile();
//        fileSystem[4]->closeFile();
    }
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
    OpenFile(OSFactory *osFactory) {
        fileSystem = osFactory;
    }

    void exec() {
        fileSystem->openFile();
    }

private:
    OSFactory *fileSystem;
};

class WriteFile : public OperatingSys {
public:
    WriteFile(OSFactory *osFactory) {
        fileSystem = osFactory;
    }

    void exec() {
        fileSystem->writeFile();
    }

private:
    OSFactory *fileSystem;
};

class CloseFile : public OperatingSys {
public:

    CloseFile(OSFactory *osFactory) {
        fileSystem = osFactory;
    }

    void exec() {
        fileSystem->closeFile();
    }

private:
    OSFactory *fileSystem;
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


/**
 * Client
 */

//class FileSystemClient {
//public:
//
//};


/**
 * Macro Command
 *
 */
class RestartCommand : public OperatingSys {
public:
    void exec() {

    }

};


int main() {
    OSFactory *factory;

//    //creating command and associating with receiver
//    OpenFile *openFileCommand = new OpenFile(factory);
//
//    //Creating invoker and associating with Command
//    FileInvoker *file = new FileInvoker(openFileCommand);
//
//    //perform action on invoker object
//    file->exec();
//
//    WriteFile *writeFileCommand = new WriteFile(factory);
//    file = new FileInvoker(writeFileCommand);
//    file->exec();
//
//    CloseFile *closeFileCommand = new CloseFile(factory);
//    file = new FileInvoker(closeFileCommand);
//    file->exec();

    char osType;
    cout << "GRUB MENU: \n"
            "Choose OS: \n "
            "l for Linux \n"
            "b for BSD \n"
            "n for WindowsNT" << endl;
    cin >> osType;

    switch (osType) {
        case 'l':
            factory = new LinuxFactory;
            break;
        case 'b':
            factory = new BSDFactory;
            break;
        case 'n':
            factory = new NTFactory;
            break;
        default:
            cout << "You did not choose a correct operating system.";
    }

    OSClient *c = new OSClient(factory);
    c->display_IO();
    delete c;
}