#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <string.h>

int format_dir(char *);
char *concatenate_args(char *, char *, char *, char *, char *, char *, char *);

char *concatenate_args(char *s1, char *repo, char *s2, char *user, char *s3, char *arg, char *s4)
{
	int i = 0;
	int j = strlen(s1) + strlen(repo) + strlen(user) + strlen(s2) + strlen(s3) + strlen(arg) + strlen(s4);
	char *result = malloc(sizeof(char) * j + 1);

	while (s1[i] != '\0') {
		result[i] = s1[i];
		i++;
	}
	j = 0;
	while (repo[j] != '\0') {
		result[i] = repo[j];
		i++;
		j++;
	}
	j = 0;
	while (s2[j] != '\0') {
		result[i] = s2[j];
		i++;
		j++;
	}
	j = 0;
	while (user[j] != '\0') {
		result[i] = user[j];
		i++;
		j++;
	}
	j = 0;
	while (s3[j] != '\0') {
		result[i] = s3[j];
		i++;
		j++;
	}
	j = 0;
	while (arg[j] != '\0') {
		result[i] = arg[j];
		i++;
		j++;
	}
	j = 0;
	while (s4[j] != '\0') {
		result[i] = s4[j];
		i++;
		j++;
	}
	result[i] = '\0';
	return (result);
}

int format_dir(char *s)
{
	int len = strlen(s);
	int i = 0;
	int j = 0;

	while (s[len-i] != '/' && len != 0)
		i++;
	j = len - i+1;
	return (j);
}

int main(int argc, char *argv[])
{
	CURL *curl;
	CURLcode res;
	char *repo = getenv("PWD");
	char *usr = getenv("USER");
	int offset = 0;

	if (argc != 2) {
		write(2, "Please enter a commit message..", 31);
		return (84);
	}
	offset = format_dir(repo);

	char *string = "payload={\"channel\": \"#commit\", \"text\": \"_";
	char *string2 = "_ : *";
	char *string3 = "* a commit : `";
	char *string4 = "`\"}";

	char *message = concatenate_args(string, repo+offset, string2, usr, string3, argv[1], string4);

	curl_global_init(CURL_GLOBAL_ALL);

	curl = curl_easy_init();
		if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "URL DU WEBHOOK ICI");
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, message);

		res = curl_easy_perform(curl);
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
		curl_easy_strerror(res));

		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	return (0);
}
