SELECT COUNT(*) FROM post WHERE author_id = 1;

SELECT COUNT(*) FROM comment WHERE post_id = 1;

INSERT INTO post (author_id, parent_id, title, meta_title, slug, summary, published, created_at, updated_at, published_at, content)
VALUES
  (1, NULL, 'Sample Post 1', 'Meta Title 1', 'sample-post-1', 'This is the summary for Sample Post 1', 1, '2023-11-07 10:00:00', NULL, '2023-11-07 10:00:00', 'This is the content for Sample Post 1'),
  (2, NULL, 'Sample Post 2', 'Meta Title 2', 'sample-post-2', 'This is the summary for Sample Post 2', 1, '2023-11-07 11:00:00', NULL, '2023-11-07 11:00:00', 'This is the content for Sample Post 2'),
  (1, 1, 'Sample Post 3', 'Meta Title 3', 'sample-post-3', 'This is the summary for Sample Post 3', 0, '2023-11-07 12:00:00', NULL, NULL, 'This is the content for Sample Post 3');