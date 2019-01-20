#! /usr/bin/env python
# -*- coding: utf-8 -*-

import paramiko
import sys


class CCmd(object):
    """
     远程执行命令类
    """

    def __init__(self, cmd_client):
        self.cmd_client = cmd_client
        self.cmd_list = ''
        self.cmd_result = ''

    def __exec_cmd(self, user_cmd):
        """
        A new Channel is opened and the requested command is executed.
        :param user_cmd:
        :return:
        """
        print('user input cmd:{}'.format(user_cmd))

        try:
            stdin, stdout, stderr = self.cmd_client.exec_command(user_cmd)
            self.cmd_result = stdout.read()
        except paramiko.SSHException:
            print('run cmd error')
            sys.exit(1)

    def get_cmd_result(self):
        """
        返回命令执行结果
        :return:
        """

        return 'exec cmd result:{}'.format(self.cmd_result)

    def run_cmd(self, __cmd):
        if len(__cmd):
            self.__exec_cmd(__cmd)
        else:
            print('cmd is empty')
            sys.exit(1)

    def add_cmd(self, cmd_cell):
        """
        添加命令
        :param cmd_cell:
        :return:
        """
        self.cmd_list += cmd_cell
        # 多条命令分隔符
        self.cmd_list += ';'

    def run_multi_cmd(self):
        """
        同时执行多个命令
        :return:
        """
        # 不要最后一个分隔符;
        cmd_list = self.cmd_list[:-1]
        if len(cmd_list):
            self.run_cmd(cmd_list)
        else:
            print('cmd is empty')
            sys.exit(1)


if __name__ == "__main__":
    pass
