#include <iostream>
#include <cstring>

class Employee
{
private:
    char *name, *programlang;
    short experience; // from 1 to 10
public:
    Employee()
    {
        experience = 0;
        name = new char[0];
        programlang = new char[0];
    }

    Employee(const char *name_, const char *programlang_, short experience_)
    {
        experience = experience_;
        name = new char[strlen(name_) + 1];
        programlang = new char[strlen(programlang_) + 1];
        strcpy(name, name_);
        strcpy(programlang, programlang_);
    }

    Employee(const Employee &rhs)
    {
        experience = rhs.experience;
        name = new char[strlen(rhs.name)+1];
        programlang = new char[strlen(rhs.programlang)+1];
        strcpy(name, rhs.name);
        strcpy(programlang, rhs.programlang);
    }

    bool operator != (const Employee &rhs)
    {
        return experience != rhs.experience || strcmp(name, rhs.name)!=0 || strcmp(programlang, rhs.programlang)!=0;
    }

    bool operator == (const Employee &rhs)
    {
        return experience == rhs.experience && strcmp(name, rhs.name) == 0 && strcmp(programlang, rhs.programlang) == 0;
    }

    Employee &operator = (const Employee &rhs)
    {
        if(this != &rhs)
        {
            setname(rhs.name);
            setprogramlang(rhs.programlang);
            setexperience(rhs.experience);
        }
        return *this;
    }

    friend std::ostream & operator << (std::ostream &os, const Employee &rhs);

    friend std::istream & operator >> (std::istream &is, const Employee &rhs);

    void setname(const char *name_)
    {
        delete[] name;
        name = new char[strlen(name_)+1];
        strcpy(name, name_);
    }

    void setprogramlang(const char *programlang_)
    {
        delete[] programlang;
        programlang = new char[strlen(programlang_)+1];
        strcpy(programlang, programlang_);
    }

    void setexperience(const short experience_)
    {
        experience = experience_;
    }

    char *getname()
    {
        return name;
    }

    char *getprogramlang()
    {
        return programlang;
    }

    short getexperience()
    {
        return experience;
    }

    ~Employee()
    {
        delete[]name;
        delete[]programlang;
    }
};

std::ostream &operator << (std::ostream & os, const Employee & rhs)
{
    os<<rhs.name<<" "<<rhs.programlang<<" "<<rhs.experience;
    return os;
}

std::istream &operator>>(std::istream &is, Employee &rhs)
{
    char name_[100], programlang_[100];
    short experience_;

    std::cout<<"Name:";
    is.getline(name_, 100);

    std::cout<<"Programming language:";
    is.getline(programlang_, 100);

    std::cout<<"Experience:";
    is>>experience_;

    rhs.setname(name_);
    rhs.setprogramlang(programlang_);
    rhs.setexperience(experience_);

    return is;
}
int main() {
    int nremployees=3;
    Employee *e = new Employee[3];

    e[0].setname("Bill Gates");
    e[0].setprogramlang("COBOL");
    e[0].setexperience(10);

    e[1].setname("Steve Jobs");
    e[1].setprogramlang("Assembly");
    e[1].setexperience(9);

    e[2].setname("Elon Musk");
    e[2].setprogramlang("Typescript");
    e[2].setexperience(5);

    int n = 1;
    while(n == 1)
    {
        std::cout<<"1 - Add employee"<<"\n";
        std::cout<<"2 - Remove employee"<<"\n";
        std::cout<<"3 - Change program language and level of experience"<<"\n";
        std::cout<<"4 - Display the employees"<<"\n";

        int q;
        std::cin>>q;
        std::cin.get();

        switch(q)
        {
            case 1:
            {
                std::cout<<"Adding new employee"<<"\n";
                nremployees++;
                Employee *aux = new Employee[nremployees];
                for(int i=0;i<nremployees-1;i++)
                    aux[i] = e[i];
                std::cin>>aux[nremployees-1];
                delete[] e;
                e = aux;
                break;
            }

            case 2:
            {
                char namefired[100];
                int k=0;
                std::cout<<"The name of the dismissed employee:";
                std::cin.getline(namefired, 100);
                Employee *aux = new Employee[nremployees-1];
                for(int i=0;i<nremployees;i++)
                    if(strcmp(namefired, e[i].getname())==0)
                    {
                        k=1;
                        break;
                    }
                if(k==0)
                {
                    std::cout<<"This employee doesn't exist"<<"\n"<<"\n"<<"\n";
                    break;
                }
                int i=0;
                for(int j=0;j<nremployees;j++)
                    if(strcmp(namefired, e[j].getname())!=0)
                        aux[i] = e[j],i++;
                delete[] e;
                e = aux;
                nremployees--;
                break;
            }

            case 3:
            {
                char nameemployee[100], program[100];
                short exp, k=0;
                std::cout<<"Employee name:";
                std::cin.getline(nameemployee, 100);
                for(int i=0;i<nremployees;i++)
                    if(strcmp(nameemployee, e[i].getname())==0)
                    {
                        k=1;
                        break;
                    }
                if(k==0)
                {
                    std::cout<<"This employee doesn't exist"<<"\n"<<"\n"<<"\n";
                    break;
                }
                std::cout<<"New program:";
                std::cin.getline(program, 100);
                std::cout<<"New level of experience:";
                std::cin>>exp;
                for(int i=0;i<nremployees;i++)
                    if(strcmp(nameemployee, e[i].getname())==0)
                    {
                        e[i].setprogramlang(program);
                        e[i].setexperience(exp);
                        break;
                    }
                break;
            }
            case 4:
                for(int i=0; i<nremployees;i++)
                    std::cout<<e[i]<<"\n";
                std::cout<<"\n";
                break;
        }
        std::cout<<"0 - Close the program"<<"\n";
        std::cout<<"1 - Go back to menu"<<"\n";

        std::cin>>n;
    }

    delete[] e;
    return 0;
}
