/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: matrus <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 10:38:09 by matrus            #+#    #+#             */
/*   Updated: 2020/11/28 10:38:12 by matrus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtest/gtest.h"
#include <stdlib.h>

int main(int argc, char **argv) {
	srand((unsigned int)time(static_cast<time_t *>(NULL)));
	::testing::InitGoogleTest(&argc, argv);

	int result = RUN_ALL_TESTS();

	return result;
}
