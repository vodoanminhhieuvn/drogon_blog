CREATE SCHEMA IF NOT EXIST blog;

CREATE TABLE IF NOT EXISTS user_
(
    id          BIGINT                   NOT NULL GENERATED ALWAYS AS IDENTITY,
    first_name  VARCHAR(50)                       DEFAULT NULL,
    middle_name VARCHAR(50)                       DEFAULT NULL,
    last_name   VARCHAR(50)                       DEFAULT NULL,
    mobile      VARCHAR(15)                       DEFAULT NULL,
    email       VARCHAR(255)                      DEFAULT NULL,
    password    text                     NOT NULL,
    role        VARCHAR(20)              NOT NULL DEFAULT 'user',
    created_at  TIMESTAMP WITH TIME ZONE NOT NULL,
    updated_at  TIMESTAMP WITH TIME ZONE          DEFAULT NULL,
    is_deleted  BOOLEAN                  NOT NULL DEFAULT FALSE,
    deleted_at  TIMESTAMP WITH TIME ZONE          DEFAULT NULL,
    last_login  TIMESTAMP WITH TIME ZONE          DEFAULT NULL,
    intro       TEXT,
    profile     TEXT,
    PRIMARY KEY (id),
    CONSTRAINT uq_mobile UNIQUE (mobile),
    CONSTRAINT uq_email UNIQUE (email)
);

CREATE TABLE IF NOT EXISTS category
(
    id         BIGINT       NOT NULL GENERATED ALWAYS AS IDENTITY,
    parent_id  BIGINT       DEFAULT NULL,
    title      VARCHAR(75)  NOT NULL,
    meta_title VARCHAR(100) DEFAULT NULL,
    slug       VARCHAR(100) NOT NULL,
    content    TEXT,
    PRIMARY KEY (id),
    CONSTRAINT fk_category_parent FOREIGN KEY (parent_id) REFERENCES category (id)
);

CREATE INDEX idx_category_parent ON category (parent_id);

CREATE TABLE IF NOT EXISTS post
(
    id           BIGINT                   NOT NULL GENERATED ALWAYS AS IDENTITY,
    author_id    BIGINT                   NOT NULL,
    parent_id    BIGINT                            DEFAULT NULL,
    title        VARCHAR(75)              NOT NULL,
    meta_title   VARCHAR(100)                      DEFAULT NULL,
    slug         VARCHAR(100)             NOT NULL,
    summary      TEXT,
    published    SMALLINT                 NOT NULL DEFAULT '0',
    created_at   TIMESTAMP WITH TIME ZONE NOT NULL,
    updated_at   TIMESTAMP WITH TIME ZONE          DEFAULT NULL,
    published_at TIMESTAMP WITH TIME ZONE          DEFAULT NULL,
    content      TEXT,
    PRIMARY KEY (id),
    CONSTRAINT uq_slug UNIQUE (slug),
    CONSTRAINT fk_post_parent FOREIGN KEY (parent_id) REFERENCES post (id),
    CONSTRAINT fk_post_user FOREIGN KEY (author_id) REFERENCES user_ (id) ON DELETE CASCADE
);

CREATE INDEX idx_post_user ON post (author_id);

CREATE INDEX idx_post_parent ON post (parent_id);

CREATE TABLE IF NOT EXISTS post_category
(
    post_id     BIGINT NOT NULL,
    category_id BIGINT NOT NULL,
    PRIMARY KEY (post_id, category_id),
    CONSTRAINT fk_pc_category FOREIGN KEY (category_id) REFERENCES category (id) ON DELETE CASCADE,
    CONSTRAINT fk_pc_post FOREIGN KEY (post_id) REFERENCES post (id) ON DELETE CASCADE
);

CREATE INDEX idx_pc_category ON post_category (category_id);

CREATE INDEX idx_pc_post ON post_category (post_id);

CREATE TABLE IF NOT EXISTS comment
(
    id           BIGINT                   NOT NULL GENERATED ALWAYS AS IDENTITY,
    post_id      BIGINT                   NOT NULL,
    user_id      BIGINT                   NOT NULL DEFAULT NULL,
    parent_id    BIGINT                            DEFAULT NULL,
    content      TEXT                     NOT NULL,
    published    SMALLINT                 NOT NULL DEFAULT '0',
    created_at   TIMESTAMP WITH TIME ZONE NOT NULL,
    published_at TIMESTAMP WITH TIME ZONE          DEFAULT NULL,
    PRIMARY KEY (id),
    CONSTRAINT fk_comment_parent FOREIGN KEY (parent_id) REFERENCES comment (id) ON DELETE CASCADE,
    CONSTRAINT fk_comment_post FOREIGN KEY (post_id) REFERENCES post (id) ON DELETE CASCADE,
    CONSTRAINT fk_comment_user FOREIGN KEY (user_id) REFERENCES user_ (id) ON DELETE CASCADE
);

CREATE INDEX idx_comment_post ON comment (post_id);

CREATE INDEX idx_comment_parent ON comment (parent_id);

CREATE INDEX idx_comment_user ON comment (user_id);

CREATE TABLE IF NOT EXISTS post_meta
(
    id      BIGINT NOT NULL GENERATED ALWAYS AS IDENTITY,
    post_id BIGINT NOT NULL,
    content TEXT,
    PRIMARY KEY (id),
    CONSTRAINT uq_post_meta UNIQUE (post_id),
    CONSTRAINT fk_meta_post FOREIGN KEY (post_id) REFERENCES post (id) ON DELETE CASCADE
);

CREATE INDEX idx_meta_post ON post_meta (post_id);

CREATE TABLE IF NOT EXISTS tag
(
    id         BIGINT       NOT NULL GENERATED ALWAYS AS IDENTITY,
    title      VARCHAR(75)  NOT NULL,
    meta_title VARCHAR(100) DEFAULT NULL,
    slug       VARCHAR(100) NOT NULL,
    content    TEXT,
    PRIMARY KEY (id)
);

CREATE TABLE IF NOT EXISTS post_tag
(
    post_id BIGINT NOT NULL,
    tag_id  BIGINT NOT NULL,
    PRIMARY KEY (post_id, tag_id),
    CONSTRAINT fk_pt_post FOREIGN KEY (post_id) REFERENCES post (id) ON DELETE CASCADE,
    CONSTRAINT fk_pt_tag FOREIGN KEY (tag_id) REFERENCES tag (id) ON DELETE CASCADE
);

CREATE INDEX idx_pt_tag ON post_tag (tag_id);

CREATE INDEX idx_pt_post ON post_tag (post_id);

