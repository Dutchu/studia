# Use Oracle Linux 7 as base image
FROM oraclelinux:7-slim

# Copy the ZIP file into the Docker image
COPY oracle_db.zip /tmp/oracle_db.zip



# Install unzip, extract the ZIP file, then clean up
RUN yum install -y unzip && \
    unzip /tmp/oracle_db.zip -d /opt/oracle && \
    rm /tmp/oracle_db.zip && \
    yum remove -y unzip && \
    yum clean all

# Set any necessary environment variables
# Set the memory target for Oracle Database
ENV MEMORY_TARGET=200M

# Execute any other setup commands
# RUN command_to_execute