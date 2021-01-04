//
//  base_utils.cc
//  Base
//
//  Created by tbago on 2021/1/2.
//  Copyright © 2021 tbago. All rights reserved.
//

#include "BaseUtils.h"

using namespace std;

string extract_file_ext(const string& path)
{
    string::size_type  pp = path.rfind('.');
    string::size_type  ps1 = path.rfind('/');
    string::size_type  ps2 = path.rfind('\\');

    if (ps1 != string::npos && ps2 != string::npos) {
        ps1 = max(ps1, ps2);
    } else if (ps1 == string::npos) {
        ps1 = ps2;
    }

    if (pp == string::npos || (ps1 != string::npos && pp < ps1))
    {
        //No extension
        return "";
    }
    else
    {
        return path.substr(pp, path.length() - pp);
    }
}

std::string extract_file_name(const std::string& path)
{
    // TODO: (tbago) not works for windows
    string::size_type lastPathStart = path.rfind("/");
    if (lastPathStart != string::npos) {
        return path.substr(lastPathStart+1);
    }
    return "";
}
