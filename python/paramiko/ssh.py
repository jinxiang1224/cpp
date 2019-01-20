#! /usr/bin/env python
# -*- coding:utf-8 -*-
import paramiko


def ssh_client(ip, user, password):
    """
    用户名和密码方式登录
    :param ip:
    :param user:
    :param password:
    :return:
    """

    try:
        ssh = paramiko.SSHClient()
        ssh.set_missing_host_key_policy(paramiko.AutoAddPolicy())
        ssh.connect(hostname=ip, port=22, username=user, password=password, timeout=10)

    except paramiko.AuthenticationException:
        raise Exception('ssh client connect error')

    return ssh


if __name__ == '__main__':
    pass
