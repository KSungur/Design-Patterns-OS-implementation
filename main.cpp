#include <iostream>
#include<vector>

using namespace std;

class FileSystem {
public:
    virtual void fileInput() = 0;

    virtual void fileOutput() = 0;

    virtual void openFile() = 0;

    virtual void writeFile() = 0;

    virtual void closeFile() = 0;
};

/**
 * Concrete Product 1
 */

class Linux : public FileSystem {
public:
    void fileInput() {
        cout << "Linux Input \n";
    }

    void fileOutput() {
        cout << "Linux Output \n";
    }

    void openFile() {
        cout << "Opening file in Linux OS" << endl;
    }

    void writeFile() {
        cout << "Writing file in Linux OS" << endl;
    }

    void closeFile() {
        cout << "Closing file in Linux OS" << endl;
    }
};

/**
 * Concrete Product 2
 */

class BSD : public FileSystem {
public:
    void fileInput() {
        cout << "BSD Input \n";
    }

    void fileOutput() {
        cout << "BSD Output \n";
    }

    void openFile() {
        cout << "Opening file in BSD OS" << endl;
    }

    void writeFile() {
        cout << "Writing file in BSD OS" << endl;
    }

    void closeFile() {
        cout << "Closing file in BSD OS" << endl;
    }
};

/**
 * Concrete Product 3
 */

class NT : public FileSystem {
public:
    void fileInput() {
        cout << "NT Input \n";
    }

    void fileOutput() {
        cout << "NT Output \n";
    }

    void openFile() {
        cout << "Opening file in Windows OS" << endl;
    }

    void writeFile() {
        cout << "Writing file in Windows OS" << endl;
    }

    void closeFile() {
        cout << "Closing file in Windows OS" << endl;
    }
};

/**
 * Abstract factory
 *
 */

class OSFactory {
public:
    virtual FileSystem *makeOutput()=0;

    virtual FileSystem *getInput()=0;
};

/**
 * Each concrete factory corresponds to one product
 * family. It creates all possible products of
 * one kind.
 */
class LinuxFactory : public OSFactory {
public:
    FileSystem *makeOutput() {
        return new Linux;
    }

    FileSystem *getInput() {
        return new Linux;
    }
};

/**
 * Concrete factory creates concrete products, but
 * returns them as abstract.
 */
class BSDFactory : public OSFactory {
public:
    FileSystem *makeOutput() {
        return new BSD;
    }

    FileSystem *getInput() {
        return new BSD;
    }
};

class NTFactory : public OSFactory {
public:
    FileSystem *makeOutput() {
        return new NT;
    }

    FileSystem *getInput() {
        return new NT;
    }
};

class OSClient {
private:
    OSFactory *factory;

public:
    OSClient(OSFactory *f) {
        factory = f;
    }

    void display_IO() {
        FileSystem *fileSystem[] = {
                factory->makeOutput(),
                factory->getInput()
        };
        fileSystem[0]->fileOutput();
        fileSystem[1]->fileInput();
    }
};

/**
 * Command Pattern
 *
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
    OpenFile(OperatingSys *operatingSys) {
        fileSystem = operatingSys;
    }

    void exec() {
        fileSystem->openFile();
    }

private:
    FileSystem *fileSystem;
};

class WriteFile : public OperatingSys {
public:
    WriteFile(OperatingSys *operatingSys) {
        fileSystem = operatingSys;
    }

    void exec(char &c) {
        fileSystem->writeFile();
    }

private:
    FileSystem *fileSystem;
};

class CloseFile : public OperatingSys {
public:

    CloseFile(OperatingSys *operatingSys) {
        fileSystem = operatingSys;
    }

    void exec(char &c) {
        fileSystem->closeFile();
    }

private:
    FileSystem *fileSystem;
};

/**
 * Invoker
 */

class FileInvoker {
public:
    OperatingSys *operatingSys;

    FileInvoker(OperatingSys os) {
        operatingSys = os;
    }
    void exec () {
        operatingSys->exec();
    }
};

/**
 * Receiver
 */

class FileSystemReceiver {
public:

};

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
    char osType;
    cout << "Choose OS; \n "
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
}