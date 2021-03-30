FROM centos:7
MAINTAINER <deetchwang@163.com>

ARG PROJ_NAME

# RUN yum install -y rsync python3-devel
# RUN pip3 install oss2

# STOPSIGNAL SIGQUIT

EXPOSE 28002

COPY $PROJ_NAME  /opt/$PROJ_NAME

WORKDIR /opt/$PROJ_NAME

ENTRYPOINT ["./docker-entrypoint.sh"]

CMD ["/usr/local/openresty/nginx/sbin/nginx", "-p", "./", "-c", "conf/docker-nginx.conf", "-g", "daemon off;"]
