#include <InputFile.hpp>
#include <OutputFile.hpp>
#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    if (argc != 3)
    {
	cerr << "Usage: " << basename(argv[0]) << " <file to read> <output file>" << endl;
        return -1;
    }
    InputFile inf(argv[1]);
    OutputFile outf(argv[2]);
    static constexpr size_t sz(64 * 1024);
    char buf[sz];
    int iret(inf.OpenIF());
    int oret(outf.OpenOF());
    for (size_t rcnt(0), wcnt(0); iret >= 0 && oret >= 0;)
    {
	if ((iret = inf.SetupRead()) < 0)
	{
		return iret;
	}
	if ((iret = inf.Read(buf, sz, rcnt)) > 0)
	{
            buf[iret] = '\0';
	    cout << buf;
            if ((oret = outf.SetupWrite(buf, iret)) < 0)
            {  
                return oret;
            }
	    if (iret < static_cast<int>(Buffer::scm_capacity))
	    {
		do
		{
                    if ((oret = outf.Write(wcnt)) > 0)
		    {
                        ++wcnt;
		    }
		}
                while (oret >= 0 && oret != iret);
		return oret != iret ? oret : 0;
	    }
	    ++rcnt;
        }
	if ((oret = outf.Write(wcnt)) < 0)
	{
            return oret;
	}
	else if (oret > 0)
	{
            ++wcnt;
	}
    }
    return (iret < oret) ? iret : oret;
}
