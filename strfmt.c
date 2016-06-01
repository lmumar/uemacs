#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "estruct.h"

static int doformati(char *dest, int v, int r)
{
	int	q, i, len;

	i = 0;
	if (v < 0) {
		dest[i++] = '-';
		v = -v;	
	}
	if ((q = v/r) != 0) {
		len = doformati(&dest[i], q, r);
		i += len;
	}
	dest[i++] = v % r + '0';
	return i;
}

static int doformat(char dest[NSTRING], const char *src, va_list ap)
{
	char	*temp;
	int	c, i;
	size_t	len;

	i = 0;
	for(;;) {
		if (i >= NSTRING || ((c=*src++) == '\0'))
			break;
		if (c != '%') {
			dest[i++] = c;
		} else {
			c = *src++;
			switch(c) {
			case 's':
				temp = va_arg(ap, char *);
				len  = strlen(temp);
				memcpy(&dest[i], temp, len);
				i += len;
				break;
			
			case 'd':
				len = doformati(&dest[i], va_arg(ap, int), 10);
				i += len;
				break;
			}
		}
	}
	len = strlen(dest);
	return len;
}

int vsformat(char dest[NSTRING], const char *fmt, va_list ap)
{
	int len;

	memset(dest, '\0', NSTRING);
	len = doformat(dest, fmt, ap);
	return len;
}
