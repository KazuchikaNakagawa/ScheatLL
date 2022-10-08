#if !defined(SCHEATINDENTMANAGERIMPL)
#define SCHEATINDENTMANAGERIMPL

#include <string>

namespace scheat
{

class IndentManagerImpl
{
private:
    unsigned int IndentCount = 0;
public:
    IndentManagerImpl();

    void IncreaseIndent() { IndentCount++; };
    void DecreaseIndent() { IndentCount--; };

    std::string getIndent();

    ~IndentManagerImpl();
};

} // namespace scheat


#endif // SCHEATINDENTMANAGERIMPL
