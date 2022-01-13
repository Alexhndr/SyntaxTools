#ifndef SYNTAX_TOOLS_COMMON_HELPER_H
#define SYNTAX_TOOLS_COMMON_HELPER_H

class Helper {
public:
    virtual ~Helper();
    bool GetIsEnding();

protected:
    bool isEnding = false;
};

#endif
