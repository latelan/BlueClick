-- phpMyAdmin SQL Dump
-- version 4.2.7
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: 2014-09-04 19:33:43
-- 服务器版本： 5.5.38-0ubuntu0.12.04.1
-- PHP Version: 5.3.10-1ubuntu3.13

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `db_blueclick`
--
CREATE DATABASE IF NOT EXISTS `db_blueclick` DEFAULT CHARACTER SET latin1 COLLATE latin1_swedish_ci;
USE `db_blueclick`;

-- --------------------------------------------------------

--
-- 表的结构 `tbl_resource`
--

CREATE TABLE IF NOT EXISTS `tbl_resource` (
`f_id` int(11) NOT NULL COMMENT '自增ID',
  `f_res_name` varchar(100) COLLATE utf8_unicode_ci NOT NULL COMMENT '资源名',
  `f_res_size` varchar(24) COLLATE utf8_unicode_ci NOT NULL COMMENT '资源大小',
  `f_res_md5` char(32) COLLATE utf8_unicode_ci NOT NULL COMMENT '资源MD5',
  `f_res_piececount` int(11) NOT NULL COMMENT '资源分片数',
  `f_reserve` varchar(32) COLLATE utf8_unicode_ci DEFAULT NULL COMMENT '保留字段'
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='资源表' AUTO_INCREMENT=90 ;

-- --------------------------------------------------------

--
-- 表的结构 `tbl_resource_owner`
--

CREATE TABLE IF NOT EXISTS `tbl_resource_owner` (
`f_id` int(11) NOT NULL COMMENT '自增ID',
  `f_res_md5` char(32) COLLATE utf8_unicode_ci NOT NULL COMMENT '资源MD5',
  `f_res_owner` char(32) COLLATE utf8_unicode_ci NOT NULL COMMENT '资源分享者',
  `f_res_sharetime` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP COMMENT '分享时间'
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='资源分享者表' AUTO_INCREMENT=83 ;

-- --------------------------------------------------------

--
-- 表的结构 `tbl_resource_tags`
--

CREATE TABLE IF NOT EXISTS `tbl_resource_tags` (
`f_id` int(11) NOT NULL COMMENT '自增ID',
  `f_res_md5` char(32) COLLATE utf8_unicode_ci NOT NULL COMMENT '资源MD5',
  `f_res_tags` varchar(32) COLLATE utf8_unicode_ci NOT NULL COMMENT '资源标识'
) ENGINE=InnoDB  DEFAULT CHARSET=utf8 COLLATE=utf8_unicode_ci COMMENT='资源标签表' AUTO_INCREMENT=300 ;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `tbl_resource`
--
ALTER TABLE `tbl_resource`
 ADD PRIMARY KEY (`f_id`), ADD UNIQUE KEY `f_res_md5` (`f_res_md5`);

--
-- Indexes for table `tbl_resource_owner`
--
ALTER TABLE `tbl_resource_owner`
 ADD PRIMARY KEY (`f_id`), ADD KEY `tbl_resource_owner` (`f_res_md5`);

--
-- Indexes for table `tbl_resource_tags`
--
ALTER TABLE `tbl_resource_tags`
 ADD PRIMARY KEY (`f_id`), ADD KEY `tbl_resource_tags` (`f_res_md5`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `tbl_resource`
--
ALTER TABLE `tbl_resource`
MODIFY `f_id` int(11) NOT NULL AUTO_INCREMENT COMMENT '自增ID',AUTO_INCREMENT=90;
--
-- AUTO_INCREMENT for table `tbl_resource_owner`
--
ALTER TABLE `tbl_resource_owner`
MODIFY `f_id` int(11) NOT NULL AUTO_INCREMENT COMMENT '自增ID',AUTO_INCREMENT=83;
--
-- AUTO_INCREMENT for table `tbl_resource_tags`
--
ALTER TABLE `tbl_resource_tags`
MODIFY `f_id` int(11) NOT NULL AUTO_INCREMENT COMMENT '自增ID',AUTO_INCREMENT=300;
--
-- 限制导出的表
--

--
-- 限制表 `tbl_resource_owner`
--
ALTER TABLE `tbl_resource_owner`
ADD CONSTRAINT `tbl_resource_owner_ibfk_1` FOREIGN KEY (`f_res_md5`) REFERENCES `tbl_resource` (`f_res_md5`);

--
-- 限制表 `tbl_resource_tags`
--
ALTER TABLE `tbl_resource_tags`
ADD CONSTRAINT `tbl_resource_tags_ibfk_1` FOREIGN KEY (`f_res_md5`) REFERENCES `tbl_resource` (`f_res_md5`),
ADD CONSTRAINT `tbl_resource_tags_ibfk_2` FOREIGN KEY (`f_res_md5`) REFERENCES `tbl_resource` (`f_res_md5`);

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
