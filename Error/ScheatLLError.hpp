#if !defined(SCHEATLLERROR_HPP)
#define SCHEATLLERROR_HPP

#include <stdexcept>

namespace scheatll
{

class scheatll_error : public std::exception
{
public:
    scheatll_error() {};

    // return the reason, not the solution.
    virtual const char* what() const noexcept override = 0;
    ~scheatll_error() {};
};

// happens when an unsuitable value, such as nullptr, was given for the functions.
class scheatll_value_error : public scheatll_error
{
public:
    scheatll_value_error() {};
    virtual const char* what() const noexcept override {
        return "unsuitable value was given";
    }
    ~scheatll_value_error() {};
};

class scheatll_expected_value_error : public scheatll_error
{
public:
    scheatll_expected_value_error() {};
    virtual const char* what() const noexcept override {
        return "clause does not have any values.";
    }
    ~scheatll_expected_value_error() {};
};

class scheatll_readability_error : public scheatll_error
{
public:
    scheatll_readability_error() {};
    virtual const char* what() const noexcept override {
        return "tried to read unreadable value";
    }
    ~scheatll_readability_error() {};
};

class scheatll_writability_error : public scheatll_error
{
public:
    scheatll_writability_error() {};
    virtual const char* what() const noexcept override {
        return "tried to write to unwritable value";
    }
    ~scheatll_writability_error() {};
};

// happens when impossible attribute --writable functions is created.
class scheatll_attribute_error : public scheatll_error
{
public:
    scheatll_attribute_error() {};
    virtual const char* what() const noexcept override {
        return "impossible attribute is generated";
    }
    ~scheatll_attribute_error() {};
};

class scheatll_name_not_exist_error : public scheatll_error
{
public:
    scheatll_name_not_exist_error() {};
    virtual const char* what() const noexcept override {
        return "given name does not exist";
    }
    ~scheatll_name_not_exist_error() {};
};

class scheatll_operator_not_exist_error : public scheatll_error
{
public:
    scheatll_operator_not_exist_error() {};
    virtual const char* what() const noexcept override {
        return "given operator does not exist";
    }
    ~scheatll_operator_not_exist_error() {};
};

class scheatll_name_already_defined_error : public scheatll_error
{
public:
    scheatll_name_already_defined_error() {};
    virtual const char* what() const noexcept override {
        return "name already defined so cannot be used";
    }
    ~scheatll_name_already_defined_error() {};
};

class scheatll_type_error : public scheatll_error
{
public:
    scheatll_type_error() {};
    virtual const char* what() const noexcept override {
        return "types are not compatible";
    }
    ~scheatll_type_error() {};
};

class scheatll_return_error : public scheatll_error
{
public:
    scheatll_return_error() {};
    virtual const char* what() const noexcept override {
        return "function return type error";
    }
    ~scheatll_return_error() {};
};

class scheatll_unavailable_feature_error : public scheatll_error
{
public:
    scheatll_unavailable_feature_error() {};
    virtual const char* what() const noexcept override {
        return "this feature is not available yet";
    }
    ~scheatll_unavailable_feature_error() {};
};

} // namespace scheatll


#endif // SCHEATLLERROR_HPP
