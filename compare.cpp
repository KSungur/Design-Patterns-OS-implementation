//#include <iostream>
//#include <vector>
//#include <string>
//
//using namespace std;
//
//class Computer;
//
/////// DEVICES
//class Device {
//public:
//    virtual void deviceReset() = 0;
//
//    virtual void increaseTemperature(int howMuch) {
//        temperature += howMuch;
//        Notify();
//    }
//
//    virtual int getTemperature() {
//        return temperature;
//    }
//
//    void Notify(); // Definition is after the Computer class because of forward declaration error...
//protected:
//    int temperature;
//    Computer *myComputer;
//};
//
//class CPU : public Device {
//    ~CPU() {
//        cout << "Terminating all processes... " << endl;
//    }
//
//public:
//
//    CPU(Computer *comp) {
//        myComputer = comp;
//        temperature = 0;
//        cout << "CPU is loading..." << endl;
//    }
//
//    void deviceReset() {
//        delete this;
//    }
//};
//
//class IO : public Device {
//    ~IO() {
//        cout << "Doing I/O things to terminate..." << endl;
//    }
//
//public:
//
//    IO(Computer *comp) {
//        myComputer = comp;
//        temperature = 0;
//        cout << "IO is loading..." << endl;
//    }
//
//    void deviceReset() {
//        delete this;
//    }
//
//};
//
//class HardDisk : public Device {
//    ~HardDisk() {
//        cout << "Writing files from buffer... " << endl;
//    }
//
//public:
//
//    HardDisk(Computer *comp) {
//        myComputer = comp;
//        temperature = 0;
//        cout << "Hard Disk is loading..." << endl;
//    }
//
//    void deviceReset() {
//        delete this;
//    }
//};
////////////////////////////////////////////////////////////////////////////////
//
/////// FILE MANAGER
//
//class FileElement {
//public:
//    virtual ~FileElement() {};
//
//    virtual void Add(FileElement *d) {};
//
//    virtual void Remove(FileElement *d) {};
//
//    virtual void Display(int indent) {};
//
//    string getName() { return name; };
//
//    virtual int getSize() = 0;
//
//    virtual FileElement *changeDir(string n) = 0;
//
//protected:
//    FileElement(string name)
//            : name(name) {};
//private:
//    string name;
//};
//
//class LinuxFile : public FileElement {
//public:
//    LinuxFile(string name) : FileElement(name) {};
//
//    void Add(FileElement *c) {
//        cout << "Cannot add to a File\n";
//    }
//
//    void Remove(FileElement *c) {
//        cout << "Cannot remove from a File \n";
//    }
//
//    void Display(int indent) {
//        for (int i = 1; i <= indent; i++) { cout << "-"; }
//        cout << " " << getName() << endl;
//    }
//
//    int getSize() {
//        return 1;
//    }
//
//    FileElement *changeDir(string n) {
//        return this;
//    }
//};
//
//class LinuxDirectory : public FileElement {
//
//public:
//    LinuxDirectory(string name) : FileElement(name) {};
//
//    void Add(FileElement *d) { elements.push_back(d); };
//
//    void Remove(FileElement *d) {
//        for (unsigned int i = 0; i < elements.size(); i++) {
//            if (elements[i]->getName() == d->getName()) {
//                elements.erase(elements.begin() + i);
//                return;
//            }
//        }
//    }
//
//    void Display(int indent) {
//        for (int i = 1; i <= indent; i++) { cout << "-"; }
//        cout << "+ " + getName() << endl;
//
//        // Display each child element on this node
//        for (unsigned int i = 0; i < elements.size(); i++) {
//            elements[i]->Display(indent + 2);
//        }
//    }
//
//    int getSize() {
//        return elements.size();
//    }
//
//    FileElement *changeDir(string n) {
//        for (int i = 0; i < elements.size(); ++i) {
//            if (elements[i]->getName() == n) {
//                return elements[i];
//            }
//        }
//        return this;
//    }
//
//private:
//    vector<FileElement *> elements;
//};
//
//class NTFile : public FileElement {
//public:
//    NTFile(string name) : FileElement(name) {};
//
//    void Add(FileElement *c) {
//        cout << "Cannot add to a File\n";
//    }
//
//    void Remove(FileElement *c) {
//        cout << "Cannot remove from a File \n";
//    }
//
//    void Display(int indent) {
//        for (int i = 1; i <= indent; i++) { cout << "-"; }
//        cout << " " << getName() << endl;
//    }
//
//    int getSize() {
//        return 1;
//    }
//
//    FileElement *changeDir(string n) {
//        return this;
//    }
//};
//
//class NTDirectory : public FileElement {
//
//public:
//    NTDirectory(string name) : FileElement(name) {};
//
//    void Add(FileElement *d) { elements.push_back(d); };
//
//    void Remove(FileElement *d) {
//        for (unsigned int i = 0; i < elements.size(); i++) {
//            if (elements[i]->getName() == d->getName()) {
//                elements.erase(elements.begin() + i);
//                return;
//            }
//        }
//    }
//
//    void Display(int indent) {
//        for (int i = 1; i <= indent; i++) { cout << "-"; }
//        cout << "+ " + getName() << endl;
//
//        // Display each child element on this node
//        for (unsigned int i = 0; i < elements.size(); i++) {
//            elements[i]->Display(indent + 2);
//        }
//    }
//
//    FileElement *changeDir(string n) {
//        for (int i = 0; i < elements.size(); ++i) {
//            if (elements[i]->getName() == n) {
//                return elements[i];
//            }
//        }
//        return this;
//    }
//
//    int getSize() {
//        return elements.size();
//    }
//
//private:
//    vector<FileElement *> elements;
//};
//
//class BSDFile : public FileElement {
//public:
//    BSDFile(string name) : FileElement(name) {};
//
//    void Add(FileElement *c) {
//        cout << "Cannot add to a File\n";
//    }
//
//    void Remove(FileElement *c) {
//        cout << "Cannot remove from a File \n";
//    }
//
//    void Display(int indent) {
//        for (int i = 1; i <= indent; i++) { cout << "-"; }
//        cout << " " << getName() << endl;
//    }
//
//    int getSize() {
//        return 1;
//    }
//
//    FileElement *changeDir(string n) {
//        return this;
//    }
//};
//
//class BSDDirectory : public FileElement {
//
//public:
//    BSDDirectory(string name) : FileElement(name) {};
//
//    void Add(FileElement *d) { elements.push_back(d); };
//
//    void Remove(FileElement *d) {
//        for (unsigned int i = 0; i < elements.size(); i++) {
//            if (elements[i]->getName() == d->getName()) {
//                elements.erase(elements.begin() + i);
//                return;
//            }
//        }
//    }
//
//    void Display(int indent) {
//        for (int i = 1; i <= indent; i++) { cout << "-"; }
//        cout << "+ " + getName() << endl;
//
//        // Display each child element on this node
//        for (unsigned int i = 0; i < elements.size(); i++) {
//            elements[i]->Display(indent + 2);
//        }
//    }
//
//    int getSize() {
//        return elements.size();
//    }
//
//    FileElement *changeDir(string n) {
//        for (int i = 0; i < elements.size(); ++i) {
//            if (elements[i]->getName() == n) {
//                return elements[i];
//            }
//        }
//        return this;
//    }
//
//private:
//    vector<FileElement *> elements;
//};
//
//
////////////////////////////////////////////////////////////////////////////////
//
///////OS
//class OS {
//protected:
//    FileElement *fileSystem;
//public:
//    OS() {}
//
//    virtual void createFileSystem(string n) = 0;
//
//    FileElement *getFileSystem() { return fileSystem; }
//
//    virtual void createFile(string n) = 0;
//
//    virtual void createDirectory(string n) = 0;
//
//    virtual void changeDirectory(string n) = 0;
//
//};
//
//class Linux : public OS {
//public:
//    void createFileSystem(string n) {
//        fileSystem = new LinuxDirectory(n);
//    }
//
//    void createFile(string n) {
//        fileSystem->Add(new LinuxFile(n));
//    }
//
//    void createDirectory(string n) {
//        fileSystem->Add(new LinuxDirectory(n));
//    }
//
//    void changeDirectory(string n) { //
//        fileSystem = fileSystem->changeDir(n);
//    }
//
//    Linux() {
//        cout << "Linux is loading..." << endl;
//        createFileSystem("root");
//    }
//};
//
//class BSD : public OS {
//public:
//    void createFileSystem(string n) {
//        fileSystem = new BSDDirectory(n);
//    }
//
//    void createFile(string n) {
//        fileSystem->Add(new BSDFile(n));
//    }
//
//    void createDirectory(string n) {
//        fileSystem->Add(new BSDDirectory(n));
//    }
//
//    void changeDirectory(string n) { //
//        fileSystem = fileSystem->changeDir(n);
//    }
//
//    BSD() {
//        cout << "BSD is loading..." << endl;
//        createFileSystem("root");
//    }
//};
//
//class NT : public OS {
//public:
//    void createFileSystem(string n) {
//        fileSystem = new NTDirectory(n);
//    }
//
//    void createFile(string n) {
//        fileSystem->Add(new NTFile(n));
//    }
//
//    void createDirectory(string n) {
//        fileSystem->Add(new NTDirectory(n));
//    }
//
//    void changeDirectory(string n) { //
//        fileSystem = fileSystem->changeDir(n);
//    }
//
//    NT() {
//        cout << "NT is loading..." << endl;
//        createFileSystem("root");
//    }
//};
//
////////////////////////////////////////////////////////////////////////////////
//
//////// TERMINAL, AND COMMAND STUFF
//class Command {
//
//public:
//    virtual void Execute() = 0;
//
//protected:
//
//    Command() {};
//};
//
//class ShutDownDevices : public Command {
//    vector<Device *> devices;
//public:
//    ShutDownDevices(vector<Device *> d) : devices(d) {}
//
//    void Execute() {
//        for (int i = devices.size() - 1; i >= 0; --i) {
//            devices[i]->deviceReset();
//        }
//    }
//};
//
//class ShowFiles : public Command {
//    FileElement *fe;
//public:
//    ShowFiles(FileElement *f) : fe(f) {}
//
//    void Execute() {
//        fe->Display(0);
//    }
//};
//
//class MakeDirectory : public Command {
//    OS *os;
//    string s;
//public:
//    MakeDirectory(OS *o) : os(o) {}
//
//    void Execute() {
//        cin >> s;
//        os->createDirectory(s);
//    }
//};
//
//class CreateFile : public Command {
//    OS *os;
//    string s;
//public:
//    CreateFile(OS *o) : os(o) {}
//
//    void Execute() {
//        cin >> s;
//        os->createFile(s);
//    }
//};
//
//class ChangeDirectory : public Command {
//    OS *os;
//    string s;
//public:
//    ChangeDirectory(OS *o) : os(o) {}
//
//    void Execute() {
//        cin >> s;
//        os->changeDirectory(s);
//    }
//};
//
//class ShowCommands : public Command {
//public:
//    ShowCommands() {}
//
//    void Execute() {
//        cout << "mkdir + [DIRNAMENAME]: Create a directory" << endl
//             << "touch + [FILENAME]: Create a file" << endl
//             << "shutdown: Close the computer" << endl
//             << "ls: display files" << endl
//             << "cd + [DIRNAME]: change directory" << endl;
//    }
//};
//
//class Terminal {
//    Command *myCommand;
//    OS *myOS;
//    string input;
//    vector<Device *> myDevices;
//    FileElement *root;
//public:
//    Terminal(OS *os, vector<Device *> dev, FileElement *ro) : myOS(os), myDevices(dev), root(ro) {}
//
//    void takeInput() {
//        while (1) {
//            cout << ">";
//            cin >> input;
//            if (input == "shutdown") {
//                myCommand = new ShutDownDevices(myDevices);
//                myCommand->Execute();
//                break;
//            } else if (input == "help") myCommand = new ShowCommands();
//            else if (input == "mkdir") {
//                myCommand = new MakeDirectory(myOS);
//                for (int i = 0; i < myDevices.size(); i++) {
//                    myDevices[i]->increaseTemperature(3);
//                }
//            } else if (input == "ls") myCommand = new ShowFiles(root);
//            else if (input == "touch") {
//                myCommand = new CreateFile(myOS);
//                for (int i = 0; i < myDevices.size(); i++) {
//                    myDevices[i]->increaseTemperature(2);
//                }
//            } else if (input == "cd") myCommand = new ChangeDirectory(myOS);
//            else continue;
//            myCommand->Execute();
//
//        }
//    }
//
//    vector<Device *> getDevices() {
//        return myDevices;
//    }
//
//};
//
//
////////////////////////////////////////////////////////////////////////////////
//
//// MASTER CLASS
//class Computer {
//    vector<Device *> devices;
//    string s;
//    OS *myOS;
//    Terminal *terminal;
//    FileElement *rootDirectory;
//    int averageTemperature;
//public:
//    Computer() {
//        devices.push_back(new IO(this));
//        devices.push_back(new CPU(this));
//        devices.push_back(new HardDisk(this));
//        cout << "Type OS's name you want to open. Current ones are Linux, BSD and NT: ";
//        cin >> s;
//        if (s == "Linux") myOS = new Linux();
//        else if (s == "BSD") myOS = new BSD();
//        else if (s == "NT") myOS = new NT();
//        rootDirectory = myOS->getFileSystem();
//        setAverageTemperature();
//        terminal = new Terminal(myOS, devices, rootDirectory);
//        terminal->takeInput();
//    }
//
//    void setAverageTemperature() {
//        int tempTemp = 0;
//        for (unsigned int i = 0; i < devices.size(); i++) {
//            tempTemp += devices[i]->getTemperature();
//        }
//        averageTemperature = tempTemp / 3;
//        if (averageTemperature > 60) cout << "Warning: Temperature is bigger than 60 degrees" << endl;
//    }
//
//    int getAverageTemperature() {
//        return averageTemperature;
//    }
//
//    ~Computer() {
//
//    };
//
//};
//
////////////////////////////////////////////////////////////////////////////////
//
//void Device::Notify() {
//    myComputer->setAverageTemperature();
//}
//
//
//int main() {
//    Computer *myComputer = new Computer();
//    delete myComputer;
//    return 0;
//}