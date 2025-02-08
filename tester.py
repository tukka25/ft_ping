# # this file is to test a.out

# import os
# import subprocess
# import sys


# def test():
# 	# get the path of the a.out
# 	path = os.path.abspath(os.path.join(os.path.dirname(__file__), 'a.out'))
# 	# run the a.out
# 	process = subprocess.Popen(path, stdout=subprocess.PIPE)
# 	# get the output
# 	output = process.communicate()[0]
# 	# print the output
# 	if (output == "b'Usage:\n  ./ft_ping [FLAG] [IP]\n\nFlags:\n  -v ===> Verbose mode\n\nIP Format:\n  xxx.xxx.xxx.xxx\n'"):
# 		print("Test Passed")

# if __name__ == '__main__':
# 	test()