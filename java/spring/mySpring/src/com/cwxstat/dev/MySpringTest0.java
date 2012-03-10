package com.cwxstat.dev;

import org.springframework.beans.factory.xml.XmlBeanFactory;

import org.springframework.core.io.ClassPathResource;

public class MySpringTest0 {

	public static void main(String[] args) {

		XmlBeanFactory beanFactory = new XmlBeanFactory(new ClassPathResource(

		"MySpring.xml"));

		MySpring myBean = (MySpring) beanFactory.getBean("MySpringBean");

		myBean.sayHello();
	}

}

