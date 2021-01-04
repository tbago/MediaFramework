//
//  base_utils.h
//  Base
//
//  Created by tbago on 2021/1/2.
//  Copyright © 2021 tbago. All rights reserved.
//

#ifndef BASE_BASE_UTILS_H_
#define BASE_BASE_UTILS_H_

#include <string>

/*!
 * @brief get file path extension, if no extension than return ""
*/
std::string extract_file_ext(const std::string& path);

/*!
@brief get file name with externsion
*/
std::string extract_file_name(const std::string& path);

#endif BASE_BASE_UTILS_H_

