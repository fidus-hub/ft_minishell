#include "execution.h"

// int     get_fd(t_cmds *cmd, t_exec *exec, int flag) // 0 for input fd | 1 for out fd
// {
//     t_file *file;
//     int     fd = 0;

//     file = cmd->file_h;
//     // t_file *file0 = cmd->file_h;
//     // t_cmds  *new_cmd = cmd;
// 	// while (new_cmd)
// 	// {
// 	// 	t_file *file0 = new_cmd->file_h;
// 	// 	// int i = 0;
// 	// 	// printf("|%s|\n",new_cmd->cmd);
// 	// 	// while (new_cmd->args[i])
// 	// 	// {
// 	// 	// 		printf("arg:%d ==> %s\n",i,new_cmd->args[i]);
// 	// 	// 		i++;
// 	// 	// }
// 	// 	while (file0)
// 	// 	{
// 	// 		printf("[type:%d][name:%s]\n",file0->type,file0->filename);
// 	// 		// printf("[%s]\n",file->filename);
// 	// 		file0 = file0->next;
// 	// 	}
// 	// 	printf("----------------------\n");
// 	// 	new_cmd = new_cmd->next;
// 	// }
//     if (file)
//     {
//         //printf("IMGERE**********************\n");
//         while (file)
//         {
//            // printf("DBG STRing: [%s]\n", file->filename);
//             if (file->type == 3) // add heredocs value 
//             {
//                 if (flag == 0)
//                 {
//                     fd = open(file->filename, O_RDONLY);
//                 }
//                 // else
//                     // fd = open(file->filename, O_CREAT | O_RDONLY);
//                 if (fd < 0)
//                 {
//                     //error;
//                 }
//                 else // FD LEAKS
//                 {
//                     //FDLEAKS;
//                 }
//             }
//             file = file->next;
//         }
//     }
//     if (fd == 0)
//     {
//         return (flag);
//     }
//     return (fd);
// }

void    ft_pipe(t_cmds *cmd, t_exec *exec)
{
    if (exec->in != 0)
    {
        // dup2(exec->in, get_fd(cmd, exec, 0));
        dup2(exec->in, 0);
        close(exec->in);
    }
    if (exec->fd[1] != 1)
    {
        // dup2(exec->fd[1], get_fd(cmd, exec, 1));
        dup2(exec->fd[1], 1);
        close(exec->fd[1]);
    }
    // if (exec->fd[0] > 2)
        close(exec->fd[0]);
}

void    ft_pipe_last(t_cmds *cmd, t_exec *exec)
{
    if (exec->in != 0)
    {
        dup2(exec->in, 0);
        close(exec->in);
    }
    if (exec->fd[1] > 2)
        close(exec->fd[1]);
}